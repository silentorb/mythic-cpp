#pragma once

#include "dllexport.h"
#include <cmath>
#include <math/utility.h>

namespace aura {

  namespace generate {

    float sine(float position) {
      return sin(position * 2 * Pi);
    }

    float triangle(float position) {
      return fabs(fmod(position, 2) - 1);
    }

    float white_noise(float position);

  }
}