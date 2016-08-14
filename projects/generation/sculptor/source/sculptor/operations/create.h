#pragma once

#include <math/utility.h>
#include "commoner/dllexport.h"

#include "sculptor/geometry.h"

using namespace sculptor::geometry;

namespace sculptor {
  namespace create {
    MYTHIC_EXPORT Basic_Mesh *square(vec2 size = vec2(1), float z = 0);

    MYTHIC_EXPORT Basic_Mesh *box(vec3 size);
    MYTHIC_EXPORT Basic_Mesh *sphere(int vertical_count, int horizontal_count,
                               float radius = 1,
                               float degrees = M_PI * 2);
  }
}