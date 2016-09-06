#include <glow.h>
#include "Square_Effect.h"

using namespace shading;

namespace drawing {

  Square_Effect::Square_Effect(Program &program) :
    Color_Effect(program), transform(program.create_property<Matrix_Property>("transform")) {

  }

  void Square_Effect::set_transform(const glm::mat4 &value) {
    transform.set(value);
  }

  void Square_Effect::activate() {
    Effect::activate();
    glow::set_depth_test(false);
    glow::set_depth_write(false);
    glow::set_blend(true);
    glow::set_blend_function(glow::Blend_Factor::source_alpha, glow::Blend_Factor::one_minus_source_alpha);
    glow::set_culling(false);
  }
}