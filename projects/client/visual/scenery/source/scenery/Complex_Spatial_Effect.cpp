#include <shading/utility.h>
#include <glow.h>
#include "Complex_Spatial_Effect.h"
#include "modeling/Mesh_Data.h"

namespace scenery {

  Complex_Spatial_Effect::Complex_Spatial_Effect(Program &program) :
    Effect(program),
    draw_method(Draw_Method::triangle_fan),
    model_property(program.create_property<shading::Matrix_Property>("model")),
    normal_property(program.create_property<shading::Matrix_Property>("normal_transform")),
    color_property(program.create_property<shading::Vector4_Property>("color_filter")) {

    color_property.set(color);
  }

  void Complex_Spatial_Effect::set_opacity(float value) {
    if (color.w == value || value == OPACITY_NOT_SET)
      return;

    color.w = value;
    color_property.set(color);
  }

  void Complex_Spatial_Effect::set_color(vec4 value) {
    if (color == value || value.w == OPACITY_NOT_SET)
      return;

    color = value;
    color_property.set(color);
  }

  void Complex_Spatial_Effect::update_shader_properties(const mat4 &transform, const mat4 &normal_transform,
                                                        bool has_opacity, const vec4 &color) {

    auto opacity_support = has_opacity || color.w != 1;
    set_color(color);
    if (culling_set)
      glow::set_culling(culling);

    shading::set_opacity_support(opacity_support);
    if (opacity_support) {
      glow::set_blend_function(blend_function);
    }
    glow::set_depth_test(depth_test);
    model_property.set(transform);
    normal_property.set(normal_transform);
  }

  void Complex_Spatial_Effect::activate(const mat4 &transform, const mat4 &normal_transform, bool has_opacity,
                                        const vec4 &color) {
    Effect::activate();
    update_shader_properties(transform, normal_transform, has_opacity, color);
  }

//  void Complex_Spatial_Effect::prepare(const mat4 &transform,
//                                       const mat4 &normal_transform,
//                                       bool has_opacity, const vec4 &color) {
//    Effect::activate();
//    update_shader_properties(transform, normal_transform, has_opacity, color);
//  }

}
