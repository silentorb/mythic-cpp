#include "Extrude.h"

namespace sculptor {
  namespace operations {
    void extrude(Edge &edge, mat4 &offset) {
      auto meshes = edge.meshes;
      Vertex* points[2];
      edge.get_ordered_points(points);
//      auto first = new Vertex();
    }
  }
}