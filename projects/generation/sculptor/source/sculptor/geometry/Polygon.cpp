#include "sculptor/geometry.h"

namespace sculptor {
  namespace geometry {

    template<typename Iterator>
    Polygon::Polygon(Iterator vertices) {
      for (Vertex *vertex: vertices) {
        vertex->polygons.push_back(this);
      }
    }
  }
}