#pragma once
#include "dllexport.h"

//#include <lookinglass/shading/Shader_Loader.h>
//#include <lookinglass/Frame.h>

namespace lookinglass {
  class MYTHIC_EXPORT Frame;
  namespace shading {
    class MYTHIC_EXPORT Shader_Loader;
  }

  class MYTHIC_EXPORT Platform_Factory {
  public:
      virtual Frame *create_frame() = 0;
      virtual shading::Shader_Loader *create_shader_loader() = 0;
  };

}
