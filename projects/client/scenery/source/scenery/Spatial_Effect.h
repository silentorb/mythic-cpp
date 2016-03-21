#pragma once

#include <shading/Shader_Property.h>
#include "dllexport.h"
#include "shading/effects/Effect.h"
#include "glm/glm.hpp"
#include "lookinglass/Draw_Method.h"

using namespace shading;
using namespace lookinglass;
using namespace glm;

namespace scenery {
  class MYTHIC_EXPORT Spatial_Effect : protected Effect {
  private:
      Draw_Method draw_method;
      float opacity = -1;
      Shader_Property model_property;
      Shader_Property normal_property;
      Shader_Property color_property;

  public:
      Spatial_Effect(Program &program);
      void activate(mat4 &transform, float opacity = 1);
      void activate(mat4 &transform, mat4 &normal_transform, float opacity = 1);

      Draw_Method get_draw_method() { return draw_method; }

      void set_draw_method(Draw_Method value) { draw_method = value; }
  };
}
