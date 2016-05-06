#pragma once

#include "dllexport.h"
#include <cmath>
#include <math/utility.h>

namespace aura {

  namespace generate {

    MYTHIC_EXPORT float sine(float position) {
      return sin(position * 2 * Pi);
    }

    MYTHIC_EXPORT float saw(float position) {
      return fabs(fmod(position, 2) - 1);
    }

//    MYTHIC_EXPORT float triangle(float position) {
//      auto value = fmod(position, 2);
//      return position > 0
//    }

    MYTHIC_EXPORT float square(float position) {
      return fmod(position, 1) < 0.5 ? 1 : -1;
    }

    MYTHIC_EXPORT float white_noise(float position);

  }
}