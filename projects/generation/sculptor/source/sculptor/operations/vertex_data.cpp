#include "vertex_data.h"
#include "sculptor/geometry/Polygon.h"

namespace sculptor {

  void set_mesh_data(geometry::Mesh &mesh, const string &attribute_name, float *values, int count) {
    for (auto &polygon: mesh.polygons) {
      polygon->set_data(attribute_name, values, count);
    }
  }
}