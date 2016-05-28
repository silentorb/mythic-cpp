#include "Composer.h"
#include "randomly/Dice.h"
#include <algorithm>

namespace aura {

  Composer::Composer() :
    dice(new randomly::Dice()) {
    dice->seed();
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

  void Composer::add_clip(int index, Clip *clip) {
    if (index >= clip_groups.size()) {
      int amount = clip_groups.size() + 1 - index;
      for (int i = 0; i < amount; ++i) {
        clip_groups.push_back(unique_ptr<Clip_Group>(new Clip_Group()));
      }
    }

    clip_groups[index]->add_clip(clip);
  }

  vector<Clip *> Composer::select_clips() {
    vector<Clip *> result;
    int max = min(max_clips, (int)clip_groups.size());
    if (clip_groups.size() < min_clips)
      throw runtime_error("Not enough clip groups to meet minimum clip setting.");

    auto amount = dice->get_int(min_clips, max);
    vector<Clip_Group *> options;
    for (auto &clip_group: clip_groups) {
      options.push_back(clip_group.get());
    }

    for (int i = 0; i < amount; ++i) {
      int index = dice->get_int(options.size());
      auto &group = *clip_groups[index];
      auto clip = group.get_random_clip(*dice);
      result.push_back(clip);
    }

    return result;
  }
}