#pragma once

#include "dllexport.h"

#include "Mesh_Data.h"
#include "sculptor/geometry.h"
#include "Vertex_Schema.h"

using namespace sculptor::geometry;

namespace modeling {
  namespace mesh_export {

    MYTHIC_EXPORT void output(Mesh &mesh, Vertex_Schema &schema, Mesh_Export &result);
    MYTHIC_EXPORT Mesh_Data *output(Mesh &mesh, Vertex_Schema &schema, bool support_lines = true);
    void register_mesh(Mesh_Data &mesh, Vertex_Schema &schema);
  }
}