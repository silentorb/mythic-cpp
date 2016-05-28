#pragma once

#include <aura/sequencing/Sequencer.h>
#include <aura/music/performance/instruments/Instrument.h>
#include "dllexport.h"
#include <memory>

using namespace std;

namespace aura {

  class MYTHIC_EXPORT Clip : no_copy {
      shared_ptr<Instrument> instrument;
      shared_ptr<Sequencer> sequencer;

  public:

      Clip(const shared_ptr<Instrument> &instrument, const shared_ptr<Sequencer> &sequencer) :
        instrument(instrument), sequencer(sequencer) { }

      Instrument &get_instrument() {
        return *instrument;
      }

      Sequencer &get_sequencer() {
        return *sequencer;
      }
  };
}