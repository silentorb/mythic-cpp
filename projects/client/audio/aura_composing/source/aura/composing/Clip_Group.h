#pragma once

#include "Clip.h"
#include <vector>
#include <memory>
#include <randomly/Dice.h>

namespace aura {
  namespace composing {

    template<typename Sound_Type, typename Event_Type>
    class Clip_Group : no_copy {
        std::vector<std::unique_ptr<Clip<Sound_Type, Event_Type>>> clips;

    public:
        void add_clip(Clip<Sound_Type, Event_Type> *clip) {
          clips.push_back(unique_ptr<Clip<Sound_Type, Event_Type>>(clip));
        }

        const std::vector <std::unique_ptr<Clip<Sound_Type, Event_Type>>> &get_clips() const {
          return clips;
        }

        Clip<Sound_Type, Event_Type> *get_random_clip(randomly::Dice &dice) {
          return clips[dice.get_int(clips.size())].get();
        }
    };
  }
}