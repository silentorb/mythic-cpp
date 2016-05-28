#include "common_processors.h"
#include <cmath>

namespace aura {

  float convert_to_db(float value) {
    return pow(value, 2);
  }
}