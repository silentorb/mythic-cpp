#pragma once

#include <memory>
#include <aura/sequencing/Sequencer.h>
#include <aura/performing/Instrument.h>

namespace aura {
  namespace composing {
    namespace sectioned {

      template<typename Sound_Type, typename Event_Type=sequencing::Note>
      class Clip {
          performing::Instrument<Sound_Type, Event_Type> *instrument;
          sequencing::Sequencer_Factory<Event_Type> *sequencer;

      public:
          Clip(performing::Instrument<Sound_Type, Event_Type> &instrument,
               sequencing::Sequencer_Factory<Event_Type> &sequencer) :
            instrument(&instrument), sequencer(&sequencer) {}

          performing::Instrument<Sound_Type, Event_Type> &get_instrument() {
            return *instrument;
          }

          sequencing::Sequencer_Factory<Event_Type> &get_sequencer() {
            return *sequencer;
          }

      };
    }
  }
}