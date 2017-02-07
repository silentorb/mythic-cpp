#pragma once

#include "commoner/dllexport.h"
#include "Note.h"
#include "Sequencer.h"
#include <vector>

using namespace std;

namespace aura {
  namespace sequencing {
    class Performer;

  class Sequence : public Sequencer {
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

      int size() const {
        return notes.size();
      }

      const Note &get_note(int index, Conductor &conductor) {
        return notes[index];
      }

      void generate_notes(Note_Consumer &consumer, Conductor &conductor) override;
  };
}}