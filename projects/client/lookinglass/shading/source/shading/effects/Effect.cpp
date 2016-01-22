#include "Effect.h"
#include "shading/Program.h"

namespace shading {

  Effect::Effect(Program &program) :
    program(&program) {

  }

  void Effect::activate() {
    program->activate();
  }
}
