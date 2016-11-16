#include "utility.h"
#include <cmath>

namespace aura {
  namespace processing {

    float dB(float value) {
//      return std::pow(value, 2);
      auto base = 10;
      return (std::pow(base, value) - 1) / (base - 1);
//      return 20 * log10(value);'
//      return std::pow(10.0f, value / 20.0f);
    }

  }
}

