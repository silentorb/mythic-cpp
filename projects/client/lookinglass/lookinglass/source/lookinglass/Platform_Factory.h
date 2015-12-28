#pragma once

//#include <lookinglass/shading/Shader_Loader.h>
//#include <lookinglass/Frame.h>

namespace lookinglass {
  class Frame;
  namespace shading {
    class Shader_Loader;
  }

  class Platform_Factory {
  public:
      virtual Frame *create_frame() = 0;
      virtual shading::Shader_Loader *create_shader_loader() = 0;
  };

}
