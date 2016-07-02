#include "Composer.h"
#include "randomly/Dice.h"
#include <algorithm>

namespace aura {

  Composer::Composer(shared_ptr<randomly::Dice> dice) :
    dice(dice) {
  }

  void Composer::add_chord_structure(Chord_Structure *structure) {
    chord_structures.push_back(unique_ptr<Chord_Structure>(structure));
  }

  void Composer::add_chord_structures(initializer_list<Chord_Structure *> structures) {
    for (auto structure: structures) {
      add_chord_structure(structure);
    }
  }

  void Composer::next_chord() {
//    current_structure_index = (current_structure_index + 1) % chord_structures.size();
    current_structure_index = dice->get_int(chord_structures.size());
  }

  void Composer::add_clip(int id, Clip *clip) {
//    if (index >= clip_groups.size()) {
//      int amount = index + 1 - clip_groups.size();
//      for (int i = 0; i < amount; ++i) {
//        clip_groups.push_back(unique_ptr<Clip_Group>(new Clip_Group()));
//      }
//    }

    if (!clip_groups.count(id))
      clip_groups[id] = unique_ptr<Clip_Group>(new Clip_Group());

    clip_groups[id]->add_clip(clip);
  }

  void Composer::add_clips(initializer_list<Clip_Group_Pair> initializer) {
    for (auto &pair: initializer) {
      add_clip(pair.group_index, new Clip(pair.instrument, pair.sequencer));
    }
  }

  vector<Clip *> Composer::select_clips() {
    vector<Clip *> result;

    int max = min(max_clips, (int) clip_groups.size());
    if (clip_groups.size() < min_clips)
      throw runtime_error("Not enough clip groups to meet minimum clip setting.");

    auto amount = dice->get_int(min_clips, max);
    vector<Clip_Group *> options;
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