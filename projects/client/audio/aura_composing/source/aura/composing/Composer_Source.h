#include "Composer.h"
#include "randomly/Dice.h"
#include <algorithm>

namespace aura {
  namespace composing {

    template<typename Sound_Type, typename Event_Type>
    Composer<Sound_Type, Event_Type>::Composer(shared_ptr<randomly::Dice> dice) :
      dice(dice) {
    }

//    template<typename Sound_Type, typename Event_Type>
//    void Composer<Sound_Type, Event_Type>::add_chord_structure(Chord_Structure *structure) {
//      chord_structures.push_back(unique_ptr<Chord_Structure>(structure));
//    }

//    template<typename Sound_Type, typename Event_Type>
//    void Composer<Sound_Type, Event_Type>::add_chord_structures(initializer_list<Chord_Structure *> structures) {
//      for (auto structure: structures) {
//        add_chord_structure(structure);
//      }
//    }

    template<typename Sound_Type, typename Event_Type>
    void Composer<Sound_Type, Event_Type>::next_chord() {
//    current_structure_index = (current_structure_index + 1) % chord_structures.size();
      current_structure_index = dice->get_int(chord_structures.size());
    }

    template<typename Sound_Type, typename Event_Type>
    void Composer<Sound_Type, Event_Type>::add_clip(int id, Clip<Sound_Type, Event_Type> *clip) {
      if (!clip_groups.count(id))
        clip_groups[id] = unique_ptr<Clip_Group<Sound_Type, Event_Type>>(new Clip_Group<Sound_Type, Event_Type>());

      clip_groups[id]->add_clip(clip);
      clip->set_group_id(id);
    }

    template<typename Sound_Type, typename Event_Type>
    void Composer<Sound_Type, Event_Type>::add_clips(initializer_list<Clip_Group_Pair<Sound_Type, Event_Type>> initializer) {
      for (auto &pair: initializer) {
        add_clip(pair.group_index, new Clip<Sound_Type, Event_Type>(pair.instrument, pair.sequencer));
      }
    }

    template<typename Sound_Type, typename Event_Type>
    vector<Clip<Sound_Type, Event_Type> *> Composer<Sound_Type, Event_Type>::select_clips() {
      vector<Clip<Sound_Type, Event_Type> *> result;

      int max = min(max_clips, (int) clip_groups.size());
      if (clip_groups.size() < min_clips)
        throw runtime_error("Not enough clip groups to meet minimum clip setting.");

      auto amount = dice->get_int(min_clips, max);
      vector<Clip_Group<Sound_Type, Event_Type> *> options;
      for (auto &pair: clip_groups) {
        options.push_back(pair.second.get());
      }

      for (int i = 0; i < amount; ++i) {
        int index = dice->get_int(options.size());
        auto group = options[index];
        options.erase(options.begin() + index);
        auto clip = group->get_random_clip(*dice);
        result.push_back(clip);
      }

      return result;
    }
  }
}