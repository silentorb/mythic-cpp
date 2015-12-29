#include "sculptor/geometry.h"

namespace sculptor {
  namespace geometry {
    Edge::Edge(Vertex *first, Vertex *second) {
      vertices[0] = first;
      vertices[1] = second;

      for (int i = 0; i < 2; ++i) {
        auto vertex = vertices[i];
        for (auto polygon: vertex->polygons) {
          if (vector_contains(polygon->vertices, vertices[1 - i])
              && !vector_contains(polygons, polygon)) {
            polygons.push_back(polygon);
          }
        }

        first->edges.push_back(this);
        second->edges.push_back(this);
      }
    }

    bool Edge::contains(Vertex *vertex) {
      return vertices[0] == vertex || vertices[1] == vertex;
    }

    void Edge::get_ordered_points(Vertex *points[2]) {
      auto other_polygon = polygons[0];
      auto p = 0;
      for (auto vertex: other_polygon->vertices) {
        if (contains(vertex))
          points[p++] = vertex;
      }

      if (points[0] == other_polygon->vertices[0]
          && points[1] == other_polygon->vertices[other_polygon->vertices.size() - 1]) {

        // Reverse the points
        auto temp = points[0];
        points[0] = points[1];
        points[1] = temp;
      }
    }

  }
}