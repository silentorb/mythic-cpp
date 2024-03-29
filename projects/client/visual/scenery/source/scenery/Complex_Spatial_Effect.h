#pragma once

#include <shading/Shader_Property.h>
#include "shading/effects/Effect.h"
#include "glm/glm.hpp"
#include "modeling/Draw_Method.h"
#include "glow.h"

namespace modeling {
  class Mesh_Data;
  class Renderable_Mesh;
}

using namespace shading;
using namespace glm;
using namespace modeling;

namespace scenery {

  const float OPACITY_NOT_SET = -1;

  class Complex_Spatial_Effect : public Effect {
      Draw_Method draw_method;
      vec4 color = vec4(1);
      glow::Blend_Function blend_function;
      bool culling_set = false;
      bool culling = true;
      bool depth_test = true;

  protected:
      Vector4_Property &color_property;
      Matrix_Property &model_property;
      Matrix_Property &normal_property;

      void update_shader_properties(const mat4 &transform, const mat4 &normal_transform, bool has_opacity,
                                    const vec4 &color);

  public:
      Complex_Spatial_Effect(Program &program);
      void activate(const mat4 &transform, const mat4 &normal_transform, bool has_opacity, const vec4 &color);

      Draw_Method get_draw_method() { return draw_method; }

      void set_draw_method(Draw_Method value) { draw_method = value; }

      void set_opacity(float value);
      void set_color(vec4 value);
      vec4 get_color() const {
        return color;
      }

//      void prepare(const mat4 &transform, const mat4 &normal_transform,
//                           bool has_opacity,
//                           const vec4 &color);

      void set_blend_function(const glow::Blend_Function value) {
        this->blend_function = value;
      }

      void set_culling(bool value){
        culling = value;
        culling_set = true;
      }

      void set_depth_test(bool value){
        depth_test = value;
      }
  };
}
