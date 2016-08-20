#include "utility.h"
#include <cmath>

namespace aura {
  namespace utility {

    float to_db(float value) {
      return std::pow(value, 2);
//      return 20 * log10(value);'
//      return std::pow(10.0f, value / 20.0f);
    }

  }
}

