#pragma once

#include "sculptor/geometry.h"

using namespace sculptor::geometry;

namespace sculptor {
  namespace operations {
    template<typename Iterator>
    void extrude(Iterator &edges, mat4 &offset, bool fill = false);
  }
}