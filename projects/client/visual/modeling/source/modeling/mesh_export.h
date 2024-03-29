#pragma once



#include "Mesh_Data.h"
#include "sculptor/geometry.h"
#include "shading/Vertex_Schema.h"

using namespace sculptor_old::geometry;

namespace modeling {
  namespace mesh_export {

    void output(const Basic_Mesh &mesh, Vertex_Schema &schema, Mesh_Export &result);
    Mesh_Data *output(const Basic_Mesh &mesh, Vertex_Schema &schema, bool support_lines = true);
    void register_mesh(Mesh_Data &mesh, Vertex_Schema &schema);
  }
}