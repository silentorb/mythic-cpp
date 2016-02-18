#pragma once

#include "dllexport.h"
#include <cstdlib>

class MYTHIC_EXPORT Random {

public:
    Random(unsigned int seed) {
      srand(seed);
    }

    float get_float() {
      return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }

    float get_float(float min, float max) {
      return min + get_float() * (max - min);
    }
};