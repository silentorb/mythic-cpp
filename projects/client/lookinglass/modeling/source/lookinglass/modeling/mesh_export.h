#pragma once

#include "Mesh_Data.h"
#include "sculptor/geometry.h"
#include "Vertex_Schema.h"

using namespace sculptor::geometry;

namespace lookinglass {
  namespace modeling {
  namespace mesh_export {

    Mesh_Data *output_textured(Mesh &mesh);
    void register_mesh(Mesh_Data &mesh, Vertex_Schema &schema);
  }
}}