#pragma once

#include "dllexport.h"
#include "Clip_Group.h"
#include <vector>
#include <memory>
#include <aura/sequencing/Chord_Structure.h>
#include <aura/sequencing/Conductor.h>

using namespace std;

namespace aura {

  class MYTHIC_EXPORT Composer {
      vector<unique_ptr<Chord_Structure>> chord_structures;
      vector<unique_ptr<Clip_Group>> clip_groups;
      int current_structure_index = 0;

  public:
      Composer();

      void add_chord_structure(Chord_Structure *structure);
      void add_chord_structures(initializer_list<Chord_Structure *> structures);

      Chord_Structure &get_current_chord_structure() const {
        return *chord_structures[current_structure_index];
      }

      void next_chord();
  };
}