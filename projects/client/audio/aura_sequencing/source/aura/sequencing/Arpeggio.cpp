#include "Arpeggio.h"

namespace aura {
  namespace sequencing {

  void create_arpeggio(Sequence &sequence, initializer_list<Pitch> initializer, float scale) {
    float offset = 0;
    for (auto &pitch: initializer) {
      sequence.add_note(Note(pitch, offset, scale));
      offset += scale;
    }
  }

//  Arpeggio *create_arpeggio(initializer_list<Pitch> initializer) {
//    auto arpeggio = new Arpeggio(initializer);
//    return arpeggio;
//  }


//  Arpeggio::Arpeggio(initializer_list<Pitch> initializer) :
//    notes(initializer) {
//
//  }
}}