#pragma once

#include "dllexport.h"
#include <cmath>
#include <math/utility.h>

namespace aura {

  namespace generate {

    MYTHIC_EXPORT float sine(float position) {
      return sin(position * 2 * Pi);
    }

    MYTHIC_EXPORT float triangle(float position) {
      return fabs(fmod(position, 2) - 1);
    }

    MYTHIC_EXPORT float white_noise(float position);

  }
}