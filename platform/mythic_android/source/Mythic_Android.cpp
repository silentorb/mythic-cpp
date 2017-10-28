#include "Mythic_Android.h"
#include "display/Android_Frame.h"
#include "display/Android_Shader_Loader.h"
#include "android_utility.h"
#include "lookinglass/House.h"
#include "../../../projects/client/general/client/source/clienting/Mythic_Client.h"
#include <iostream>
#include "logger.h"
#include "input/Android_Input.h"
#include "audio/Android_Speaker.h"
#include <shading/shader_processing.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include "lookinglass/Graphic_Options.h"

Mythic_Android::Mythic_Android(Android_App *app, lookinglass::Graphic_Options &graphic_options) :
  app(app), initializer(nullptr), engine(nullptr), graphic_options(new lookinglass:: Graphic_Options(graphic_options)) {
  app->userData = this;
  android_initialize_utility(app->activity->assetManager);
  client = nullptr;
}

Mythic_Android::~Mythic_Android() {
  if (client)
    delete client;
}

framing::Platform_Frame *Mythic_Android::create_frame(const lookinglass::Graphic_Options &graphic_options) {
  return new Android_Frame(app);
}

//shading::Shader_Loader *Mythic_Android::create_shader_loader() {
//  return new Android_Shader_Loader(app->activity->assetManager);
//}

static void engine_handle_cmd(struct Android_App *app, int32_t command) {
  auto mythic = (Mythic_Android *) app->userData;
  mythic->process_command(command);
}

void Mythic_Android::process_command(int32_t command) {
  switch (command) {
    case APP_CMD_SAVE_STATE:
      log_info("Workbench APP_CMD_SAVE_STATE.");
      break;
    case APP_CMD_INIT_WINDOW:
      log_info("Workbench APP_CMD_INIT_WINDOW.");

      // The window is being shown, get it ready.
      if (ready == -1) {
        ready = 0;
      }
      else if (ready == 2) {
        engine->get_client().load();
//        set_render(true);
      }

      break;
    case APP_CMD_TERM_WINDOW:
      log_info("Workbench APP_CMD_TERM_WINDOW.");
      if (engine.get())
        engine->get_client().release();
//      get_frame().free();
      break;

    case APP_CMD_GAINED_FOCUS:
//      set_render(true);
      log_info("Workbench APP_CMD_GAINED_FOCUS.");

      break;
    case APP_CMD_LOST_FOCUS:
      log_info("Workbench APP_CMD_LOST_FOCUS.");
      if (engine.get())
        set_render(false);

      break;
  }
}

void Mythic_Android::start() {
  static bool initialized = false;
  if (initialized)
    return;

  log_info("starting mythic engine.");
//  activity->setVolumeControlStream();
  auto storage = get_storage_path();
  if (!std::ifstream(storage)) {
    log_info("Creating file folder (%s)", storage.c_str());
    mkdir(storage.c_str(), 0770);
  }

  {
    auto temp_path = storage + "frog.txt";
    {
      ofstream myfile;
      myfile.open(temp_path);
      myfile << "Written by a frog.\n";
    }
    {
      ifstream file;
      file.open(temp_path);
      if (!file.good())
        throw std::runtime_error(string("Could not open ") + temp_path);

      stringstream stream;
      stream << file.rdbuf();
      log_info("Message: %s", stream.str().c_str());
    }
  }
  initialized = true;
  log_info("creating_client");

  engine = unique_ptr<mythic::Mythic_Engine>{new mythic::Mythic_Engine(*this, *graphic_options)};

  engine->get_client().load();

  if (initializer) {
    log_info("loading myths.");
    initializer(*engine, *this);
  }

  log_info("mythic engine is running.");

//  workshop_exiting = true;
}

int32_t on_input(Android_App *app, AInputEvent *event) {

  log_info("Input pressed.");
  auto mythic = (Mythic_Android *) app->userData;
  mythic->process_input(event);
  return 0;
}

void Mythic_Android::process_input(AInputEvent *event) {

  if (AInputEvent_getType(event) == 2 && AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_UP && ready == 0)
    ready = 1;
  else if (ready == 2) {
    android_input->process_input(event);
  }

}

bool Mythic_Android::is_closing() {
  if (!engine)
    return false;

  return engine->get_client().is_closing();
}

void Mythic_Android::poll() {
  int ident;
  int events;
  struct android_poll_source *source;

  while ((ident = ALooper_pollAll(0, NULL, &events,
                                  (void **) &source)) >= 0) {

    // Process this event.
    if (source != NULL) {
      source->process(app, source);
    }

    if (ready == 1) {
      start();
      ready = 2;
    }
  }
}

void Mythic_Android::run() {
  ready = -1;
  app->onInputEvent = on_input;
  app->onAppCmd = engine_handle_cmd;

  try {
    while (!is_closing()) {

      poll();

      if (ready == 2) {
        engine->update();
      }

      // Check if we are exiting.
      if (app->destroyRequested != 0) {
        log_info("Abandon bench.");
//          engine_term_display(&engine);
        return;
      }
    }
  }
  catch (exception &e) {
    auto message = e.what();
    std::cout << message;
    log_error("Mythic Android - Critical Error: %s", e.what());
  }

  catch (...) {
    log_warning("Unkown Mythic Error.");
  }
}

haft::Input_Source *Mythic_Android::create_input_source(haft::Input_Configuration &config) {
  android_input = new Android_Input(config);
  return android_input;
}

void Mythic_Android::set_render(bool value) {
  engine->get_client().get_house().set_active(value);
}

//Android_Frame &Mythic_Android::get_frame() const {
//  return (Android_Frame &) engine->get_client().get_house().get_frame();
//}


audio::Speaker *Mythic_Android::create_speaker() {
  return new Android_Speaker();
}

platforming::Shader_Processor Mythic_Android::create_shader_processor() {
  return [](shading::Shader_Type type, const string &source) {
//    log_info("Loaded shader: %s", source);
    auto included = shading::process_includes(source, type, platforming::File_Loader(android_load_string));
//    log_info("Loaded shader includes: %s", source);
    return string("precision highp float;\n\n") + shading::olden(included, type);

//      return "#version 430\n" + shading::process_includes(source, type, resourceful::File_Loader(Desktop_File_Loader));
  };
}

platforming::File_Loader Mythic_Android::create_file_loader() {
  return android_load_string;
}

const string Mythic_Android::get_storage_path() {
  ANativeActivity *activity = app->activity;
  const char *internal_path = activity->internalDataPath;
  return internal_path + string("/");
}