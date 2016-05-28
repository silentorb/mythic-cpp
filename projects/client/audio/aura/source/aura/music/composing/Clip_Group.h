#pragma once

#include "dllexport.h"
#include "Clip.h"
#include <vector>
#include <memory>

namespace randomly {
  class Dice;
}

using namespace std;

namespace aura {

  class MYTHIC_EXPORT Clip_Group : no_copy {
      vector<unique_ptr<Clip>> clips;

  public:
      void add_clip(Clip * clip) {
        clips.push_back(unique_ptr<Clip>(clip));
      }

      const vector<unique_ptr<Clip>> &get_clips() const {
        return clips;
      }

      Clip* get_random_clip(randomly::Dice &dice);
  };
}