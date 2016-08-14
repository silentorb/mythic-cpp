#pragma once

#include "commoner/dllexport.h"
#include <cmath>
#include <math/utility.h>

namespace aura {

  namespace generate {

    MYTHIC_EXPORT float sine(float position);
    MYTHIC_EXPORT float saw(float position);
    MYTHIC_EXPORT float square(float position);
    MYTHIC_EXPORT float white_noise(float position);

  }
}