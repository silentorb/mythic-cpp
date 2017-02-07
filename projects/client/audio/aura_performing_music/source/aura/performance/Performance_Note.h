#pragma once

#include <aura/performing/Instrument.h>
#include <aura/sequencing/Note.h>

namespace aura {
  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Performance_Note {
        Instrument <Sound_Type, Event_Type> *instrument;
        sequencing::Note note;

    public:
        Performance_Note(Instrument <Sound_Type, Event_Type> &instrument, const sequencing::Note &note) :
          instrument(&instrument), note(note) {}

        Instrument <Sound_Type, Event_Type> &get_instrument() const {
          return *instrument;
        }

        const Note &get_note() const {
          return note;
        }
    };
  }
}