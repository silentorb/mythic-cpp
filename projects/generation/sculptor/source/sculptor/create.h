#pragma once

#include <math/utility.h>
#include "dllexport.h"

#include "sculptor/geometry.h"

using namespace sculptor::geometry;

namespace sculptor {
  namespace create {
    MYTHIC_EXPORT  Mesh *box(vec3 size);
    MYTHIC_EXPORT Mesh *sphere(int vertical_count, int horizontal_count, float radius, float degrees = M_PI * 2);
  }
}