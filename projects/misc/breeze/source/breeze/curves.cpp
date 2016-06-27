#include "curves.h"

namespace breeze {
  namespace curves {

    float linear(float value) {
      return value;
    }

    float bezier(float value) {
      return value * value * (3.0f - 2.0f * value);
    }
  }
}

