#pragma once

#include <aura/sequencing/Sequencer.h>
#include "Instrument.h"

using namespace aura::sequencing;

namespace aura {
  namespace performing {

    class Performance {
        Instrument &instrument;
        Sequencer &sequencer;
        int group_id;

    public:
        Performance(Instrument &instrument, Sequencer &sequencer, int group_id)
          : instrument(instrument), sequencer(sequencer), group_id(group_id) {}

        ~Performance() {

        }
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
}