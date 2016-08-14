#pragma once

#include <aura/sequencing/Sequencer.h>
#include <aura/music/performance/Instrument.h>
#include "commoner/dllexport.h"
using namespace aura::music::performance;
using namespace aura::sequencing;

namespace aura {

  class MYTHIC_EXPORT Performance {
      Instrument &instrument;
      Sequencer &sequencer;
      int group_id;

  public:
      Performance(Instrument &instrument, Sequencer &sequencer, int group_id)
        : instrument(instrument), sequencer(sequencer), group_id(group_id) { }

      Instrument &get_instrument() const {
        return instrument;
      }

      Sequencer &get_sequencer() const {
        return sequencer;
      }

      int get_group_id() const {
        return group_id;
      }
  };
}