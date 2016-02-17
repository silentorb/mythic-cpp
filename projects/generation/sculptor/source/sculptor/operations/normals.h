#pragma once

#include "dllexport.h"
#include "sculptor/geometry/Mesh.h"

using namespace sculptor::geometry;

namespace sculptor {

  MYTHIC_EXPORT void flatten_normals(Mesh &mesh);
}