#include <desktop/Desktop_Input.h>
#include "Desktop.h"
#include "desktop/Desktop_Frame.h"
#include "desktop/Desktop_Shader_Loader.h"
#include "logger.h"
#include "clienting/Client.h"

using namespace lookinglass;

namespace desktop {

  Desktop::Desktop(const char *title) : title(title) {
    engine = unique_ptr<Mythic_Engine>(new Mythic_Engine(*this));
    engine->get_client().load();
  }

  Frame *Desktop::create_frame() {
    return new Desktop_Frame(title);
  }

  shading::Shader_Loader *Desktop::create_shader_loader() {
    return new Desktop_Shader_Loader("resources/shaders");
  }

  haft::Input_Source *Desktop::create_input_source(haft::Input_Configuration & config) {
    return new Desktop_Input(config);
  }

  const char * get_resource_path() {
    return "resources";
  }

}

