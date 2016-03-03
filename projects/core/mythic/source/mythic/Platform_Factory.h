#pragma once

#include "dllexport.h"

namespace haft {
  class Input_Source;
  class Input_Configuration;
}

namespace shading {
  class Shader_Loader;
}

namespace lookinglass {

  class Frame;
};
using namespace lookinglass;

namespace mythic {

  class MYTHIC_EXPORT Platform_Factory {
  public:
      virtual Frame *create_frame(int width, int height) = 0;
      virtual shading::Shader_Loader *create_shader_loader() = 0;
      virtual haft::Input_Source *create_input_source(haft::Input_Configuration & config) = 0;
  };

}
