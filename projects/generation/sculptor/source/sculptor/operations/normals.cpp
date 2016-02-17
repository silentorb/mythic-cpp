#include "normals.h"
#include "sculptor/geometry/Polygon.h"
#include "sculptor/geometry/Vertex.h"

namespace sculptor {

  void flatten_normals(Mesh &mesh) {
    for (auto &polygon: mesh.polygons) {
      auto normal = polygon->get_normal();
      polygon->set_data("normal", (float *) & normal, 3);
    }
  }
}