#pragma once

#include <math/utility.h>
#include "sculptor/geometry.h"

using namespace sculptor::geometry;

namespace sculptor {
  namespace create {
    Basic_Mesh *square(vec2 size = vec2(1), float z = 0);

    Basic_Mesh *box(vec3 size);
    Basic_Mesh *sphere(int vertical_count, int horizontal_count,
                               float radius = 1,
                               float degrees = M_PI * 2);
  }
}