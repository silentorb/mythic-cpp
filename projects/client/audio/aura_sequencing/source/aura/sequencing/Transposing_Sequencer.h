#pragma once

#include "commoner/dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>

using namespace std;

namespace aura {
  namespace sequencing {

    template<typename Event_Type>
    class Transposing_Sequencer : public Sequencer<Event_Type> {
        shared_ptr<Sequence<Event_Type>> event_source;
        Chord_Source &chord_source;

    public:
        Transposing_Sequencer(shared_ptr<Sequence<Event_Type>> &source, Chord_Source &chord_source) :
          event_source(source), chord_source(chord_source) {
        }

        virtual ~Transposing_Sequencer() {}

        float get_beats() const {
          return event_source->get_beats();
        }

        int size() const {
          return event_source->size();
        }

        const Note get_note(int index) {
          auto note = event_source->get_note(index);
          auto &pitch = transpose(*note.get_pitch(), chord_source.get_chord());
          return Note(pitch, note.get_start(), note.get_duration());
        }

        void generate_notes(Event_Consumer<Event_Type> &consumer) override {
          for (int i = 0; i < event_source->size(); ++i) {
            consumer.add_event(get_note(i));
          }
        }
    };

  }
}