#pragma once

#include "sculptor/geometry.h"

using namespace sculptor::geometry;

namespace sculptor {
  namespace operations {
    void extrude(Edge &edge, mat4 &offset);
  }
}