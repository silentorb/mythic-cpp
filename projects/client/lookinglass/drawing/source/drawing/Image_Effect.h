#pragma once

#include "dllexport.h"
#include "shading/effects/Effect.h"
#include "glm/fwd.hpp"

namespace modeling {
  class Simple_Mesh;
}

namespace lookinglass {
  namespace perspective {
    class Viewport;
  }
}

using namespace glm;

namespace drawing {

  class MYTHIC_EXPORT Image_Effect : protected shading::Effect {
      lookinglass::perspective::Viewport &viewport;

  public:
      Image_Effect(shading::Program &program, lookinglass::perspective::Viewport &viewport);

      void render(const mat4 &transform, modeling::Simple_Mesh &mesh, const mat4 &texture_transform);
  };

}
