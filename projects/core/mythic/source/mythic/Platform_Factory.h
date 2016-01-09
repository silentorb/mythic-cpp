#pragma once

#include "dllexport.h"

namespace haft {
  class Input_Source;
}

namespace lookinglass {

  class MYTHIC_EXPORT Frame;

  namespace shading {
    class MYTHIC_EXPORT Shader_Loader;
  }
};
using namespace lookinglass;

namespace mythic {

  class MYTHIC_EXPORT Platform_Factory {
  public:
      virtual Frame *create_frame() const = 0;
      virtual shading::Shader_Loader *create_shader_loader() const = 0;
      virtual haft::Input_Source *create_input_source() const = 0;
  };

}
