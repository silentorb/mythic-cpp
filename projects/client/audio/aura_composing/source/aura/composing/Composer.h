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
  namespace composing {

    template<typename Sound_Type, typename Event_Type>
    struct Clip_Group_Pair {
        int group_index;
        performing::Instrument<Sound_Type, Event_Type> &instrument;
        Sequencer_Factory<Event_Type> sequencer;
    };

    template<typename Sound_Type, typename Event_Type>
    class Composer : no_copy {
        std::vector<std::unique_ptr<Chord_Structure>> chord_structures;
        std::map<int, std::unique_ptr<Clip_Group<Sound_Type, Event_Type>>> clip_groups;
        int current_structure_index = 0;
        std::shared_ptr<randomly::Dice> dice;
        int min_clips = 2;
        int max_clips = 6;

    public:
        Composer(std::shared_ptr<randomly::Dice> dice);

        void add_chord_structure(Chord_Structure *structure) {
          chord_structures.push_back(unique_ptr<Chord_Structure>(structure));
        }

        void add_chord_structures(initializer_list<Chord_Structure *> structures) {
          for (auto structure: structures) {
            add_chord_structure(structure);
          }
        }

        Chord_Structure &get_current_chord_structure() const {
          return *chord_structures[current_structure_index];
        }

        void add_clip(int id, Clip<Sound_Type, Event_Type> *clip);
        void add_clips(std::initializer_list<Clip_Group_Pair<Sound_Type, Event_Type>> initializer);

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

        vector<Clip<Sound_Type, Event_Type> *> select_clips();
    };
  }
}