#pragma once

#include "dllexport.h"

#include "Mesh_Data.h"
#include "sculptor/geometry.h"
#include "Vertex_Schema.h"

using namespace sculptor::geometry;

namespace modeling {
  namespace mesh_export {

    MYTHIC_EXPORT Mesh_Data *output(Mesh &mesh, Vertex_Schema & schema);
    void register_mesh(Mesh_Data &mesh, Vertex_Schema &schema);
  }
}