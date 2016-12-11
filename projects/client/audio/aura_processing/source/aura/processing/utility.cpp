#include "utility.h"
#include <cmath>

namespace aura {
  namespace processing {

//    constexpr float dB(float value) {
////      return std::pow(value, 2);
////      const auto base = 10;
//      return (std::pow(10, value) - 1) / (10 - 1);
////      return 20 * log10(value);'
////      return std::pow(10.0f, value / 20.0f);
//    }

    float inverse_dB(float value) {
      const auto base = 10;
      return (std::pow(base, 1 - value) + 1) / (base - 1) + 1;
    }
  }
}

