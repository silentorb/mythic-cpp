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
        shared_ptr<Sequence<Event_Type>> source;
        Note return_note;

    public:
        Transposing_Sequencer(shared_ptr<Sequence<Event_Type>> &source) :
          source(source), return_note(Note(pitches::A4, 0, 1)) {
        }

        virtual ~Transposing_Sequencer() {}

        float get_beats() const {
          return source->get_beats();
        }

        int size() const {
          return source->size();
        }

        const Note &get_note(int index, Conductor &conductor) {
          auto note = source->get_note(index, conductor);
          auto &pitch = transpose(*note.get_pitch(), conductor.get_chord());
          return_note = Note(pitch, note.get_start(), note.get_duration());
          return return_note;
        }

        void generate_notes(Event_Consumer<Event_Type> &consumer, Conductor &conductor) override {
          for (int i = 0; i < source->size(); ++i) {
            consumer.add_event(get_note(i, conductor));
          }
        }
    };

    const Pitch &transpose(const Pitch &pitch, const Chord_Instance &chord);
  }
}