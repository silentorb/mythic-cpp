#pragma once

#include "lookinglass/Mesh_Data.h"
#include "sculptor/geometry/Mesh.h"

using namespace sculptor:: geometry;

namespace lookinglass {
  namespace mesh_export {

    Mesh_Data* ooutput_textured(Mesh & mesh);
  }
}