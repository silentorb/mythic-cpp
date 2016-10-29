#include "Chord_Structure.h"

namespace aura {
  namespace sequencing {

  Chord_Structure::Chord_Structure(initializer_list<Chord_Instance> initializer) : chords(initializer) {
    for (auto &chord: chords) {
      measures += chord.duration;
    }
  }

  void Chord_Structure::set_chords(initializer_list<Chord_Instance> initializer) {
    for (auto &chord: initializer) {
      chords.push_back(chord);
      measures += chord.duration;
    }
  }


}}