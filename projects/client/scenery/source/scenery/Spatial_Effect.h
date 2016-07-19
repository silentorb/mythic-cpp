#pragma once

#include <shading/Shader_Property.h>
#include "dllexport.h"
#include "shading/effects/Effect.h"
#include "glm/glm.hpp"
#include "modeling/Draw_Method.h"
#include "lookinglass/glow.h"

namespace modeling {
  class Mesh_Data;
}
//namespace glow {
//  struct Blend_Function;
//}

using namespace shading;
using namespace glm;
using namespace modeling;

namespace scenery {

  const float OPACITY_NOT_SET = -1;

  class MYTHIC_EXPORT Spatial_Effect : protected Effect {
  private:
      Draw_Method draw_method;
      float opacity = 1;
      glow::Blend_Function blend_function;
//      void activate(mat4 &transform, bool has_opacity, float opacity);

  protected:
      Vector4_Property color_property;
      Matrix_Property model_property;
      Matrix_Property normal_property;

      void update_shader_properties(mat4 &transform, mat4 &normal_transform, bool has_opacity, float opacity);

  public:
      Spatial_Effect(Program &program);
      void activate(mat4 &transform, mat4 &normal_transform, bool has_opacity, float opacity);

      Draw_Method get_draw_method() { return draw_method; }

      void set_draw_method(Draw_Method value) { draw_method = value; }

      void set_opacity(float value);
      virtual void render(modeling::Mesh_Data *mesh_data, mat4 &transform, mat4 &normal_transform, bool has_opacity,
                          float opacity);

      void set_blend_function(const glow::Blend_Function value) {
        this->blend_function = value;
      }
  };
}
