#include "signal_generators.h"
#include "randomly/Dice.h"

randomly::Dice dice;

namespace aura {

  namespace generate {

    float smooth;

    float white_noise(float position) {
      auto sample = dice.get_float(-1, 1);
//    return sample;
//    float amount = 1 - position;
      float amount = 0.5;
      smooth = smooth - (amount * (smooth - sample));
      return smooth;
    }


    float sine(float position) {
      return (float)sin(position * 2 * Pi);
    }

    float saw(float position) {
      return (float)fabs(fmod(position, 2) - 1);
    }

//    MYTHIC_EXPORT float triangle(float position) {
//      auto value = fmod(position, 2);
//      return position > 0
//    }

    float square(float position) {
      return fmod(position, 1) < 0.5 ? 1 : -1;
    }
  }
}

