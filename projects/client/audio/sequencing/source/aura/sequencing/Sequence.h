#pragma once

#include "dllexport.h"
#include "Note.h"
#include "Sequencer.h"
#include <vector>

using namespace std;

namespace aura {
  class Performer;

  class MYTHIC_EXPORT Sequence : public Sequencer {
      vector<Note> notes;
      float beats = 0;

  public:

      Sequence() { }

      Sequence(initializer_list<const Note> initializer, float beats) : beats(beats) {
        add_notes(initializer);
      }

      Sequence(float offset, float note_length, initializer_list<const Note> initializer, float beats) : beats(beats) {
        add_notes(offset, note_length, initializer);
      }

//      void update(float offset);
      void add_note(const Note &note);
      void add_notes(initializer_list<const Note> initializer);
      void add_notes(float offset, float note_length, initializer_list<const Note> initializer);

      const vector<Note> &get_notes() const {
        return notes;
      }

      float get_beats() const {
        return beats;
      }

      void set_beats(float value) {
        beats = value;
      }

      virtual int size() const override {
        return notes.size();
      }

      virtual const Note &get_note(int index, Conductor &conductor) override {
        return notes[index];
      }


  };
}