#include "Color_Effect.h"

namespace shading {

  Color_Effect::Color_Effect(Program &program)
    : Effect(program), color(program.create_property<Vector4_Property>("color")) {

  }

  void Color_Effect::set_color(const vec4 &value) {
    color.set(value);
  }
}