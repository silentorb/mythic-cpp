#pragma once

#include "dllexport.h"
#include "shading/effects/Effect.h"
#include "glm/fwd.hpp"

namespace modeling {
  class Simple_Mesh;
}

using namespace glm;

namespace drawing {
  class MYTHIC_EXPORT Image_Effect : protected shading::Effect {
//      modeling::Simple_Mesh &mesh;
      mat4 projection;

      Image_Effect &operator=(const Image_Effect &) = delete;
      Image_Effect(Image_Effect const &) = delete;
  public:
      Image_Effect(shading::Program &program, const ivec2 &viewport_dimensions);

      void render(const mat4 &transform, modeling::Simple_Mesh &mesh, const mat4 &texture_transform);

      void initialize_projection(const ivec2 &viewport_dimensions);
      void modify_projection(mat4 &modifier);
  };

}
