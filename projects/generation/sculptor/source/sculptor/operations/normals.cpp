#include "normals.h"
#include "sculptor/geometry/Polygon.h"
#include "sculptor/geometry/Vertex.h"

namespace sculptor {

  void flatten_normals(Mesh &mesh) {
    for (auto &polygon: mesh.polygons) {
      auto normal = polygon->calculate_normal();

      vector <vec3> data;
      for (int i = 0; i < polygon->vertices.size(); ++i) {
        data.push_back(normal);
      }

      polygon->add_data("normal", (float *) data.data(), data.size() * 3);
    }
  }
}