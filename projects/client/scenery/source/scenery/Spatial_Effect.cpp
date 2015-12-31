#include "Spatial_Effect.h"

namespace scenery {
  Spatial_Effect::Spatial_Effect(Program &program) :
    Effect(program),
    draw_method(Draw_Method::triangles) {

  }

  void Spatial_Effect::activate(mat4 &transform) {
    Effect::activate();
  }
}
