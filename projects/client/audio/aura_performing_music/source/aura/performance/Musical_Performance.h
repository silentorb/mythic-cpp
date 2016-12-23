#pragma once

#include <aura/sequencing/Sequencer.h>
#include "Instrument_Old.h"

using namespace aura::sequencing;

namespace aura {
  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Musical_Performance {
        Instrument<Sound_Type, Event_Type> &instrument;
        Sequencer &sequencer;
        int group_id;

    public:
        Musical_Performance(Instrument<Sound_Type, Event_Type> &instrument, Sequencer &sequencer, int group_id)
          : instrument(instrument), sequencer(sequencer), group_id(group_id) {}

        ~Musical_Performance() {

        }
        Instrument<Sound_Type, Event_Type> &get_instrument() const {
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