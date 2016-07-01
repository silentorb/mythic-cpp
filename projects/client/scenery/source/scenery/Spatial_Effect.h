#pragma once

#include <shading/Shader_Property.h>
#include "dllexport.h"
#include "shading/effects/Effect.h"
#include "glm/glm.hpp"
#include "modeling/Draw_Method.h"

using namespace shading;
using namespace glm;
using namespace modeling;

namespace scenery {

  const float OPACITY_NOT_SET = -1;

  class MYTHIC_EXPORT Spatial_Effect : protected Effect {
  private:
      Draw_Method draw_method;
      float opacity = 1;
      Matrix_Property model_property;
      Matrix_Property normal_property;
      Vector4_Property color_property;

  public:
      Spatial_Effect(Program &program);
      void activate(mat4 &transform, bool has_opacity, float opacity);
      void activate(mat4 &transform, mat4 &normal_transform, bool has_opacity, float opacity);

      Draw_Method get_draw_method() { return draw_method; }

      void set_draw_method(Draw_Method value) { draw_method = value; }

      void set_opacity(float value);
  };
}
