#include <shading/utility.h>
#include <lookinglass/glow.h>
#include "Spatial_Effect.h"
#include "modeling/Mesh_Data.h"

namespace scenery {
  Spatial_Effect::Spatial_Effect(Program &program) :
    Effect(program),
    draw_method(Draw_Method::triangles),
    model_property(program.create_property<shading::Matrix_Property>("model")),
    normal_property(program.create_property<shading::Matrix_Property>("normal_transform")),
    color_property(program.create_property<shading::Vector4_Property>("color_filter")) {

//    Effect::activate();
    color_property.set(color);
  }

  void Spatial_Effect::set_opacity(float value) {
    if (color.w == value || value == OPACITY_NOT_SET)
      return;

    color.w = value;
    color_property.set(color);
  }

  void Spatial_Effect::set_color(vec4 value) {
    if (color == value || value.w == OPACITY_NOT_SET)
      return;

    color = value;
    color_property.set(color);
  }

  void Spatial_Effect::activate(mat4 &transform, mat4 &normal_transform, bool has_opacity, vec4 &color) {
    Effect::activate();
    update_shader_properties(transform, normal_transform, has_opacity, color);
  }

  void Spatial_Effect::update_shader_properties(const mat4 &transform, const mat4 &normal_transform, bool has_opacity,
                                                const vec4 &color) {

    auto opacity_support = has_opacity || color.w != 1;
    set_color(color);
    shading::set_opacity_support(opacity_support);
    if (opacity_support) {
      glow::set_blend_function(blend_function);
    }
    glow::set_depth_test(true);
    model_property.set(transform);
    normal_property.set(normal_transform);
  }

  void Spatial_Effect::render(Mesh_Data *mesh_data, const mat4 &transform, const mat4 &normal_transform,
                              bool has_opacity, const vec4 &color) {
    Effect::activate();
    update_shader_properties(transform, normal_transform, has_opacity, color);
    mesh_data->draw(get_draw_method());
  }

}
