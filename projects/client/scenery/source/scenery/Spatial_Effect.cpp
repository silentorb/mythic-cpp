#include <shading/utility.h>
#include <lookinglass/glow.h>
#include "Spatial_Effect.h"

namespace scenery {
  Spatial_Effect::Spatial_Effect(Program &program) :
    Effect(program),
    draw_method(Draw_Method::triangles),
    model_property("model", &program),
    normal_property("normal_transform", &program),
    color_property("color_filter", program) { }

  void Spatial_Effect::activate(mat4 &transform, bool has_opacity, float opacity) {
    Effect::activate();
    shading::set_opacity_support(has_opacity);
    glow::set_depth_test(true);

    model_property.set(transform);

    if (opacity != this->opacity) {
      this->opacity = opacity;
      color_property.set(1, 1, 1, opacity);
    }
  }

  void Spatial_Effect::activate(mat4 &transform, mat4 &normal_transform, bool has_opacity, float opacity) {
    activate(transform, has_opacity, opacity);
    normal_property.set(normal_transform);

    if (opacity != this->opacity) {
      this->opacity = opacity;
      color_property.set(1, 1, 1, opacity);
    }
  }
}
