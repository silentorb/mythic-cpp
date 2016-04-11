#include "Composer.h"

namespace aura {

  Composer::Composer() { }

  void Composer::add_chord_structure(Chord_Structure *structure) {
    chord_structures.push_back(unique_ptr<Chord_Structure>(structure));
  }

  void Composer::add_chord_structures(initializer_list<Chord_Structure *> structures) {
    for (auto structure: structures) {
      add_chord_structure(structure);
    }
  }
}