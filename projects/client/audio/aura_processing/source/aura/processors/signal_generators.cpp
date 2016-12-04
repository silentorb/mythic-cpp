#include "signal_generators.h"
#include "randomly/Dice.h"

randomly::Dice dice;

namespace aura {

  namespace generate {

    float smooth;

    float white_noise() {
      auto sample = dice.get_float(-1, 1);
      float amount = 0.5;
      smooth = smooth - (amount * (smooth - sample));
      return smooth;
    }

    float white_noise_dummy_position(float position) {
      return white_noise();
    }

    float sine(float position) {
      return (float)sin(position * 2 * Pi);
    }

    float saw(float position) {
      return (float)fabs(fmod(position, 2) - 1);
    }

//    float triangle(float position) {
//      auto value = fmod(position, 2);
//      return position > 0
//    }

    float square(float position) {
      return fmod(position, 1) < 0.5 ? 1 : -1;
    }

    float triangle(float position){
      float x = fmod(position, 1);
      float a = x * 4;
      if (x < 0.25)
        return a;

      if (x < 0.75)
        return 2 - a;

      return a - 4;
    }
  }
}

