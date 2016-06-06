#pragma once

#include <memory>
#include "mythic/Platform_Factory.h"
#include "android_native_app_glue.h"
#include "mythic/Mythic_Engine.h"

using namespace std;
class Android_Frame;

namespace lookinglass {

  class MYTHIC_EXPORT Frame;

};

namespace shading {
  class MYTHIC_EXPORT Shader_Loader;
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

    android_app *app;
    void start();
    Mythic_Initializer initializer;
    unique_ptr<Mythic_Engine> engine;
    clienting::Client *client;

    bool is_closing();
    int ready = 0;
    void set_render(bool value);

    Android_Frame & get_frame() const;
    Android_Input*android_input;
    void poll();

public:
    Mythic_Android(android_app *app);
    ~Mythic_Android();

    Frame *create_frame(int width, int height) override;
    shading::Shader_Loader *create_shader_loader() override;
    haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;
    void run();

    void process_command(int32_t command);
    void process_input(AInputEvent *event);

    void set_initializer(Mythic_Initializer initializer) {
      this->initializer = initializer;
    }

    virtual audio::Speaker *create_speaker() override;

    Mythic_Engine &get_engine() const {
      return *engine.get();
    }
};

