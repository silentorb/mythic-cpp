#pragma once

#include "Clip_Group.h"
#include <vector>
#include <memory>
#include <aura/sequencing/Chord_Structure.h>
#include <aura/sequencing/Conductor.h>
#include <map>

namespace randomly {
  class Dice;
}

using namespace std;

namespace aura {

  struct Clip_Group_Pair {
      int group_index;
      shared_ptr<Instrument> instrument;
      shared_ptr<Sequencer> sequencer;
  };

  class MYTHIC_EXPORT Composer : no_copy {
      vector<unique_ptr<Chord_Structure>> chord_structures;
      map<int, unique_ptr<Clip_Group>> clip_groups;
      int current_structure_index = 0;
      shared_ptr<randomly::Dice> dice;
      int min_clips = 2;
      int max_clips = 6;

  public:
      Composer(shared_ptr<randomly::Dice> dice);

      void add_chord_structure(Chord_Structure *structure);
      void add_chord_structures(initializer_list<Chord_Structure *> structures);

      Chord_Structure &get_current_chord_structure() const {
        return *chord_structures[current_structure_index];
      }

      void add_clip(int id, Clip *clip);
      void add_clips(initializer_list<Clip_Group_Pair> initializer);

      void next_chord();

      int get_min_clips() const {
        return min_clips;
      }

      void set_min_clips(int min_clips) {
        Composer::min_clips = min_clips;
      }

      int get_max_clips() const {
        return max_clips;
      }

      void set_max_clips(int max_clips) {
        Composer::max_clips = max_clips;
      }

      vector<Clip *> select_clips();
  };
}