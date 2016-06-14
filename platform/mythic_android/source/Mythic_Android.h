#pragma once

#include <memory>
#include "mythic/Platform_Factory.h"
#include "Android_App.h"
#include "mythic/Mythic_Engine.h"
#include "logger.h"

using namespace std;
class Android_Frame;

namespace framing {

  class Platform_Frame;

};

namespace shading {
  class Shader_Loader;
}

namespace clienting {
  class Client;
}
namespace audio {
  class Speaker;
}
using namespace mythic;

using namespace lookinglass;
class Android_Input;

typedef void (*Mythic_Initializer)(Mythic_Engine &engine);

class Mythic_Android : public Platform_Factory {
private:

    Android_App *app;
    void start();
    Mythic_Initializer initializer;
    unique_ptr<Mythic_Engine> engine;
    clienting::Client *client;

    bool is_closing();
    int ready = 0;
    void set_render(bool value);

//    Android_Frame & get_frame() const;
    Android_Input*android_input;
    void poll();

public:
    Mythic_Android(Android_App *app);
    ~Mythic_Android();

    framing::Platform_Frame *create_frame(int width, int height) override;
    haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;
    void run();

    void process_command(int32_t command);
    void process_input(AInputEvent *event);

    void set_initializer(Mythic_Initializer initializer) {
      log_info("Setting mythic android initializer.");
      this->initializer = initializer;
    }

    virtual audio::Speaker *create_speaker() override;

    Mythic_Engine &get_engine() const {
      return *engine.get();
    }

    virtual mythic::Shader_Processor create_shader_processor() override;
    virtual mythic::File_Loader create_file_loader() override;
    virtual const string get_storage_path() override;

};

