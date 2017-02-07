#pragma once

#include "commoner/dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>

using namespace std;

namespace aura {
  namespace sequencing {

    class Transposing_Sequencer : public Sequencer {
        shared_ptr<Sequence> source;
        Note return_note;

    public:
        Transposing_Sequencer(shared_ptr<Sequence> &source) :
          source(source), return_note(Note(pitches::A4, 0, 1)) {
        }

        virtual ~Transposing_Sequencer() {}

        float get_beats() const {
          return source->get_beats();
        }

        int size() const {
          return source->size();
        }

        const Note &get_note(int index, Conductor &conductor);
        void generate_notes(Note_Consumer &consumer, Conductor &conductor) override;
    };

    const Pitch &transpose(const Pitch &pitch, const Chord_Instance &chord);
  }
}