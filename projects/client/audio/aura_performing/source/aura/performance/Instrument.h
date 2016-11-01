#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <aura_export.h>

namespace aura {

    namespace sequencing {
      class Note;
    }

  namespace performing {
    class Musical_Stroke;

    class AURA_EXPORT Instrument {

      public:
          virtual Musical_Stroke *generate_stroke(const aura::sequencing::Note &note) = 0;

          virtual ~Instrument() {}
      };
    }
  }