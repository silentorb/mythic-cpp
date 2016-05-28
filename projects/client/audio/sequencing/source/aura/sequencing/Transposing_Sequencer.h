#pragma once

#include "dllexport.h"
#include "Sequencer.h"
#include "Arpeggio.h"
#include <memory>

using namespace std;

namespace aura {

  class MYTHIC_EXPORT Transposing_Sequencer : public Sequencer {
      shared_ptr<Sequence> source;
      Note return_note;

  public:
      Transposing_Sequencer(shared_ptr<Sequence> &source) :
        source(source), return_note(Note(pitches::A4, 0, 1)) {
      }

      virtual float get_beats() const override {
        return source->get_beats();
      }

      virtual int size() const override {
        return source->size();
      }

      virtual const Note &get_note(int index, Conductor &conductor) override;
  };

  const Pitch &transpose(const Pitch &pitch, const Chord_Instance &chord);

}