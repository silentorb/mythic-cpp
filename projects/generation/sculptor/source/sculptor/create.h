#pragma once
#include "dllexport.h"

#include "sculptor/geometry.h"

using namespace sculptor::geometry;

namespace sculptor {
  namespace create {
    MYTHIC_EXPORT  Mesh *box(vec3 size);
  }
}