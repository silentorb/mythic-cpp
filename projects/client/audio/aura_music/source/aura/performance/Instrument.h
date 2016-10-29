#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <aura_export.h>

namespace aura {
  class Musical_Stroke;

  namespace sequencing {
    class Note;
  }

  namespace performance {

    class AURA_EXPORT Instrument {

    public:
        virtual Musical_Stroke *generate_stroke(const aura::sequencing::Note &note) = 0;

        virtual ~Instrument() {}
    };
  }
}