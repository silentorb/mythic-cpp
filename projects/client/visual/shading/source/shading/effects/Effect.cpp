#include "Effect.h"
#include "shading/Program.h"
#include "glow.h"
#include "glow_gl.h"

namespace shading {

  Effect *active_effect = nullptr;

  Effect::Effect(Program &program) :
    program(&program) {

  }

  void Effect::activate() {
//    if (active_effect == this)
//      return;

    active_effect = this;
    program->activate();
  }

  Effect::~Effect() {
      }
}
