#pragma once

#include <aura/sequencing/Sequencer.h>
#include <aura/music/performance/instruments/Instrument.h>
#include "dllexport.h"

namespace aura {

  class MYTHIC_EXPORT Performance {
      Instrument &instrument;
      Sequencer &sequencer;

  public:
      Performance(Instrument &instrument, Sequencer &sequencer) : instrument(instrument), sequencer(sequencer) { }

      Instrument &get_instrument() const {
        return instrument;
      }

      Sequencer &get_sequencer() const {
        return sequencer;
      }
  };
}