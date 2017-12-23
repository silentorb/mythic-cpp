#pragma once


#include "Sequence.h"

namespace aura {
  namespace sequencing {

    typedef vector<Pitch> Arpeggio;

    template<typename Event_Type>
    void create_arpeggio(Sequence<Event_Type> &sequence, initializer_list<Pitch> initializer, float scale = 1) {
      float offset = 0;
      for (auto &pitch: initializer) {
        sequence.add_event(Note(pitch, offset, scale));
        offset += scale;
      }
    }
//  Arpeggio *create_arpeggio(initializer_list<Pitch> initializer);


//  class Arpeggio {
//      vector<Pitch> notes;
//
//  public:
//      Arpeggio(initializer_list<Pitch> initializer);
//
//  };
  }
}