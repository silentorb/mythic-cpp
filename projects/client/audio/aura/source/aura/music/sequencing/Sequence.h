#pragma once

#include "dllexport.h"
#include "Note.h"
#include <vector>

using namespace std;

namespace aura {
  class Performer;

  class MYTHIC_EXPORT Sequence {
      vector<Note> notes;
      float seconds = 0;

  public:
//      void update(float offset);
      void add_note(const Note &note);
      void add_notes(initializer_list<Note> initializer);
      void perform(Performer & performer, float start, float end);

      const vector<Note> &get_notes() const {
        return notes;
      }

      float get_seconds() const {
        return seconds;
      }
  };
}