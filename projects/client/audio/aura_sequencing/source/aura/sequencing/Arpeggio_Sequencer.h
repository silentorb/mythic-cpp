#pragma once

#include "commoner/dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>
#include "Transposing_Sequencer.h"

using namespace std;

namespace aura {
  namespace sequencing {

    template<typename Event_Type = Note>
    class Arpeggio_Sequencer : public Sequencer<Event_Type> {
        const Arpeggio &arpeggio;
        float beats_per_note;
        float beats;
        Chord_Source &chord_source;

    public:
        Arpeggio_Sequencer(const Arpeggio &arpeggio, Chord_Source &chord_source, float beats_per_note) :
          arpeggio(arpeggio), chord_source(chord_source) {
          set_beats_per_note(beats_per_note);
        }

//        Arpeggio_Sequencer(Arpeggio *arpeggio,Chord_Source & chord_source, float beats_per_note) :
//          arpeggio(arpeggio), chord_source(chord_source) {
//          set_beats_per_note(beats_per_note);
//        }

        virtual ~Arpeggio_Sequencer() {}

        float get_beats() const {
          return beats;
        }

        int size() const {
          return arpeggio.size();
        }

        const Event_Type get_event(int index) {
          auto &pitch = transpose(arpeggio.at(index), chord_source.get_chord());
          return Note(pitch, index * beats_per_note, beats_per_note);
        }

        void set_beats_per_note(float value) {
          beats_per_note = value;
          beats = beats_per_note * arpeggio.size();
        }

        void generate_notes(Event_Consumer<Event_Type> &consumer) override {
          for (int i = 0; i < arpeggio.size(); ++i) {
            consumer.add_event(get_event(i));
          }
        }
    };
  }
}