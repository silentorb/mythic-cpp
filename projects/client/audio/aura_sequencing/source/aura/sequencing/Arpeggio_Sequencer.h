#pragma once

#include "commoner/dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>

using namespace std;

namespace aura {
  namespace sequencing {

    class Arpeggio_Sequencer : public Sequencer {
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

        virtual ~Arpeggio_Sequencer() { }

        virtual float get_beats() const override {
          return beats;
        }

        virtual int size() const override {
          return arpeggio->size();
        }

//      const Pitch &transpose(Pitch &pitch, const Chord_Instance &chord);

        virtual const Note &get_note(int index, Conductor &conductor) override;

        void set_beats_per_note(float value) {
          beats_per_note = value;
          beats = beats_per_note * arpeggio->size();
        }
    };
  }
}