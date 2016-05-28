#include "Clip_Group.h"
#include <randomly/Dice.h>

namespace aura {

  Clip *Clip_Group::get_random_clip(randomly::Dice &dice) {
    return clips[dice.get_int(clips.size())].get();
  }

}