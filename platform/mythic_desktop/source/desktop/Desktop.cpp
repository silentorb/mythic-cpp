#include <desktop/Desktop_Input.h>
#include <audio/Speaker.h>
#include "Desktop.h"
#include "desktop/Desktop_Frame.h"
#include "logger.h"
#include "clienting/Client.h"
#include <desktop_audio/interface.h>
#include "Desktop_File_Loader.h"

using namespace lookinglass;

namespace desktop {

  Desktop::Desktop(const char *title, int width, int height) : title(title) {
    engine = unique_ptr<Mythic_Engine>(new Mythic_Engine(*this, width, height));
    engine->get_client().load();
  }

  Frame *Desktop::create_frame(int width, int height) {
    return new Desktop_Frame(title, width, height);
  }

//  shading::Shader_Loader *Desktop::create_shader_loader() {
//    return new Desktop_Shader_Loader("resources/shaders");
//  }

  haft::Input_Source *Desktop::create_input_source(haft::Input_Configuration &config) {
    return new Desktop_Input(config);
  }

  audio::Speaker *Desktop::create_speaker() {
    return desktop_create_speaker();
  }

  const char *get_resource_path() {
    return "resources";
  }

  mythic::Shader_Processor Desktop::create_shader_processor() {
    return [](shading::Shader_Type type, const string &source) {
      return "#version 330\n" + source;
    };
  }

  mythic::File_Loader Desktop::create_file_loader() {
    return Desktop_File_Loader;
  }

}

