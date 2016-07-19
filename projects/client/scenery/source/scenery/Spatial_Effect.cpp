#include <shading/utility.h>
#include <lookinglass/glow.h>
#include "Spatial_Effect.h"
#include "modeling/Mesh_Data.h"

namespace scenery {
  Spatial_Effect::Spatial_Effect(Program &program) :
    Effect(program),
    draw_method(Draw_Method::triangles),
    model_property("model", &program),
    normal_property("normal_transform", &program),
    color_property("color_filter", program) {

    Effect::activate();
    color_property.set(1, 1, 1, opacity);
  }

  void Spatial_Effect::set_opacity(float value) {
    if (opacity == value || value == OPACITY_NOT_SET)
      return;

    opacity = value;
    color_property.set(1, 1, 1, opacity);
  }

  void Spatial_Effect::activate(mat4 &transform, mat4 &normal_transform, bool has_opacity, float opacity) {
    Effect::activate();
    update_shader_properties(transform, normal_transform, has_opacity, opacity);
  }

  void Spatial_Effect::update_shader_properties(mat4 &transform, mat4 &normal_transform, bool has_opacity,
                                                float opacity) {

    auto opacity_support = has_opacity || this->opacity != 1;
    set_opacity(opacity);
    shading::set_opacity_support(opacity_support);
    if (opacity_support) {
      glow::set_blend_function(blend_function);
    }
    glow::set_depth_test(true);
    model_property.set(transform);
    normal_property.set(normal_transform);
  }

  void Spatial_Effect::render(modeling::Mesh_Data *mesh_data, mat4 &transform, mat4 &normal_transform, bool has_opacity,
                              float opacity) {
    Effect::activate();
    update_shader_properties(transform, normal_transform, has_opacity, opacity);
    mesh_data->draw(get_draw_method());
  }

}
