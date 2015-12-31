#pragma once

#include "dllexport.h"

namespace lookinglass {
  namespace shading {
    class Program;

    namespace effects {

      class MYTHIC_EXPORT Effect {
      protected:
          Program *const program;

      public:
          Effect(Program &program);
          void activate();
      };
    }
  }
}