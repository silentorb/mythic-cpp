#include "Effect.h"
#include "lookinglass/shading/Program.h"

namespace lookinglass {
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
}
