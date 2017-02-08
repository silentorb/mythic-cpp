#pragma once

#include "commoner/dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>
#include "Transposing_Sequencer.h"

using namespace std;

namespace aura {
  namespace sequencing {

    template<typename Event_Type>
    class Arpeggio_Sequencer : public Sequencer<Event_Type> {
        shared_ptr<Arpeggio> arpeggio;
        float beats_per_note;
        float beats;
        Note return_note;

    public:
        Arpeggio_Sequencer(const shared_ptr<Arpeggio> &arpeggio, float beats_per_note) :
          arpeggio(arpeggio), return_note(Note(pitches::A4, 0, 1)) {
          set_beats_per_note(beats_per_note);
        }

        Arpeggio_Sequencer(Arpeggio *arpeggio, float beats_per_note) :
          arpeggio(arpeggio), return_note(Note(pitches::A4, 0, 1)) {
          set_beats_per_note(beats_per_note);
        }

        virtual ~Arpeggio_Sequencer() {}

        float get_beats() const {
          return beats;
        }

        int size() const {
          return arpeggio->size();
        }

        const Note &get_note(int index, Conductor &conductor) {
          auto &pitch = transpose(arpeggio->at(index), conductor.get_chord());
          return_note = Note(pitch, index * beats_per_note, beats_per_note);
          return return_note;
        }

        void set_beats_per_note(float value) {
          beats_per_note = value;
          beats = beats_per_note * arpeggio->size();
        }

        void generate_notes(Event_Consumer<Event_Type> &consumer, Conductor &conductor) override {
          for (int i = 0; i < arpeggio->size(); ++i) {

          }
        }
    };
  }
}