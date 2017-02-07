#pragma once

#include <aura/sequencing/Sequencer.h>
#include <aura/sequencing/utility.h>
#include <aura/performing/Instrument.h>

using namespace aura::sequencing;

namespace aura {
  namespace performing {

    template<typename Sound_Type>
    class Stroke_Input {
    public:
        virtual void add_stroke(unique_ptr<Sound_Type> stroke) = 0;
    };

    template<typename Sound_Type, typename Event_Type>
    class Musical_Performance {
        Instrument <Sound_Type, Event_Type> &instrument;
        Sequencer &sequencer;

    public:
        Musical_Performance(Instrument <Sound_Type, Event_Type> &instrument, Sequencer &sequencer)
          : instrument(instrument), sequencer(sequencer) {}

        ~Musical_Performance() {

        }

        Instrument <Sound_Type, Event_Type> &get_instrument() const {
          return instrument;
        }

        Sequencer &get_sequencer() const {
          return sequencer;
        }

        void update(Stroke_Input<Sound_Type> &input, Conductor &conductor, float start, float end) {
          start *= sequencer.get_beats();
          end *= sequencer.get_beats();

          for (int i = 0; i < sequencer.size(); ++i) {
            auto &note = sequencer.get_note(i, conductor);
            if (sequencing::is_inside(note.get_start(), start, end)) {
              input.add_stroke(instrument.create_sound(note));
            }
          }
        }
    };
  }
}