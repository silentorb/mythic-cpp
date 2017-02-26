#pragma once

#include <memory>
#include <aura/sequencing/Sequencer.h>
#include <aura/performing/Instrument.h>

using namespace std;
using namespace aura::sequencing;

namespace aura {
  namespace composing {

    template<typename Sound_Type, typename Event_Type>
    class Clip : no_copy {
        performing::Instrument<Sound_Type, Event_Type> &instrument;
        Sequencer_Factory<Event_Type> sequencer;
        int group_id = -1;

    public:
        Clip(performing::Instrument<Sound_Type, Event_Type> &instrument, const Sequencer_Factory<Event_Type> &sequencer) :
          instrument(instrument), sequencer(sequencer) {}

        performing::Instrument<Sound_Type, Event_Type> &get_instrument() {
          return instrument;
        }

        Sequencer_Factory<Event_Type> &get_sequencer() {
          return sequencer;
        }

        int get_group_id() const {
          return group_id;
        }

        void set_group_id(int value) {
          group_id = value;
        }
    };
  }
}