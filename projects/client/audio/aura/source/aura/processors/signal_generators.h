#pragma once

#include "commoner/dllexport.h"
#include <cmath>
#include <math/utility.h>

namespace aura {

  namespace generate {

    float sine(float position);
    float saw(float position);
    float square(float position);
    float white_noise_dummy_position(float position);
    float white_noise();

  }
}