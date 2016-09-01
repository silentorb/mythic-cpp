#include "Color_Effect.h"

namespace shading {

  Color_Effect::Color_Effect(Program &program)
    : Effect(program) {

  }

  void Color_Effect::activate(const vec4 &value) {
    Effect::activate();
    auto index = get_location("color");
    set_vec4(index, value);

  }
}