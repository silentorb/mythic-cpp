#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <aura/performing/Instrument.h>

namespace aura {

  namespace sequencing {
    class Note;
  }

  namespace performing {
    class Musical_Stroke;

    using Instrument_Old = Instrument<Musical_Stroke, sequencing::Note>;
//    class Instrument_Old {
//
//    public:
//        virtual Musical_Stroke *generate_stroke(const aura::sequencing::Note &note) = 0;
//
//        virtual ~Instrument_Old() {}
//    };
  }
}