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
        virtual void add_stroke(std::unique_ptr<Sound_Type> stroke) = 0;
    };

    template<typename Sound_Type, typename Event_Type = aura::sequencing::Note>
    class Musical_Performance {
        Instrument <Sound_Type, Event_Type> *instrument;
        std::unique_ptr<Sequencer<Event_Type>> sequencer;

    public:
        Musical_Performance(Instrument <Sound_Type, Event_Type> &instrument,
                            std::unique_ptr<Sequencer<Event_Type>> &sequencer)
          : instrument(&instrument), sequencer(std::move(sequencer)) {}

        Musical_Performance(Musical_Performance &&other)
          : instrument(other.instrument), sequencer(std::move(other.sequencer)) {

        }

        Musical_Performance(Musical_Performance const &) = delete;
        Musical_Performance &operator=(Musical_Performance const &) = delete;

        Musical_Performance &operator=(Musical_Performance &&other) {
          instrument = other.instrument;
          sequencer = std::move(other.sequencer);
          return *this;
        }

        ~Musical_Performance() {

        }

        Instrument <Sound_Type, Event_Type> &get_instrument() const {
          return *instrument;
        }

        Sequencer<Event_Type> &get_sequencer() const {
          return *sequencer;
        }
    };

    template<typename Sound_Type, typename Event_Type>
    class Performance_Source {
    public:
        virtual Instrument <Sound_Type, Event_Type> &get_instrument() = 0;
        virtual std::unique_ptr<Sequencer<Event_Type>> get_sequencer() = 0;
    };
  }
}