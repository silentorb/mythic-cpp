#pragma once

#include "dllexport.h"
#include <modeling/Simple_Mesh.h>
#include "shading/effects/Effect.h"
#include "glm/fwd.hpp"

using namespace glm;

namespace drawing {
  class MYTHIC_EXPORT Image_Effect : protected shading::Effect {
      modeling::Simple_Mesh &mesh;

  public:
      Image_Effect(shading::Program &program, modeling::Simple_Mesh &mesh);

      void render(const mat4 &transform, const ivec2 &viewport_dimensions);
  };

}
