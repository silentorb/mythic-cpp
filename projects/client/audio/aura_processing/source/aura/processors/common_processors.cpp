#include "common_processors.h"
#include <cmath>

namespace aura {

  float to_db(float value) {
//    return pow(value, 2);
    auto base = 10;
    return (std::pow(base, value) - 1) / (base - 1);
  }
}