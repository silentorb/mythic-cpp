#include "Color_Effect.h"

namespace shading {

  void Color_Effect::set_color(const vec4 &value) {
    auto index = get_location("color");
    set_vec4(index, value);
  }
}