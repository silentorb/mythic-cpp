#include "Effect.h"
#include "shading/Program.h"

  namespace shading {
    namespace effects {

      Effect::Effect(Program &program) :
        program(&program) {

      }

      void Effect::activate() {
        program->activate();
      }
    }
  }
