#include <cmath>
#include <math/utility.h>
#include "angle.h"

namespace spatial {
  float z_angle(float y, float x) {
    auto angle = (float)(atan2(y, x));
    if (angle < 0)
      angle += (float)Pi * 2;

    return angle;
  }
}