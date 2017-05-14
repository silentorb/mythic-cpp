#include "utility.h"
#include <cmath>

namespace aura {
  namespace processing {

//    float to_dB(float value) {
//      return (std::pow(10, value) - 1) / (10 - 1);
//    }

    float inverse_dB(float value) {
      const auto base = 10;
      return (std::pow(base, 1 - value) + 1) / (base - 1) + 1;
    }
  }
}

