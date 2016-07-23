#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <aura_export.h>

namespace sequencing {
  class Note;
}
namespace aura {
  class Stroke;
  namespace music {
    namespace performance {
      class AURA_EXPORT Instrument {
        

        public:
          virtual Stroke* generate_stroke(const aura::sequencing::Note& note) = 0;
          virtual ~Instrument() {}
      };
    }
  }
}