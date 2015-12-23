#include "Spatial_Effect.h"

namespace lookinglass {
  namespace scenery {
    Spatial_Effect::Spatial_Effect() :
      draw_method(Draw_Method::triangles) {

    }

    void Spatial_Effect::activate(mat4 &transform) {
      Effect::activate();
    }
  }
}