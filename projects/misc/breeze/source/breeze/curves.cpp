#include "curves.h"

namespace breeze {
  namespace curves {

    float linear(float value) {
      return value;
    }

    float bezier(float value) {
      return value * value * (3.0f - 2.0f * value);
    }

    float cubic(float value) {
      const float scale = 2 * 2 * 2; // 2 * 2 * 2 * 2 * 0.5

      if (value <= 0.5)
        return value * value * value * value * scale;

      value -= 1;
      return value * value * value * value * -scale + 1;
    }
  }
}

