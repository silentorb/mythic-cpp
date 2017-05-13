#pragma once

#include "commoner/dllexport.h"
#include <cmath>
#include <math/utility.h>

namespace randomly {
  class Dice;
}

namespace aura {

  namespace generate {

    namespace ranged {
      float triangle(float position);
    }

      void initialize();
    float sine(float position);
    float cosine(float position);
    float saw(float position);
    float square(float position);
    float square_pulse_width(float position, float pulse_width);
    float white_noise_dummy_position(float position);
    float white_noise();
    float white_noise(randomly::Dice &dice);
    float triangle(double position);

  }

}