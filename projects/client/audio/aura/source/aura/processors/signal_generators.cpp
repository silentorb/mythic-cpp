#include "signal_generators.h"
#include "randomly/Dice.h"

randomly::Dice dice;

namespace aura {
  float smooth;

  float ::aura::generate::white_noise(float position) {
    auto sample = dice.get_float(-1, 1);
//    return sample;
//    float amount = 1 - position;
    float amount = 0.5;
    smooth = smooth - (amount * (smooth - sample));
    return smooth;
  }


}

