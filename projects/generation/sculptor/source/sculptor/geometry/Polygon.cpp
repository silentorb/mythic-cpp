#include <vectoring/utility.h>
#include "sculptor/geometry.h"

namespace sculptor {
  namespace geometry {

    template<typename Iterator>
    Polygon::Polygon(Iterator source) {
      for (Vertex *vertex : source) {
        add_vertex(vertex);
      }

      initialize();
    }

    Polygon::Polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth) {
      add_vertex(first);
      add_vertex(second);
      add_vertex(third);
      add_vertex(fourth);
      uvs = nullptr;

      initialize();
    }

    Polygon::Polygon(Vertex *first, Vertex *second, Vertex *third) {
      add_vertex(first);
      add_vertex(second);
      add_vertex(third);
      uvs = nullptr;

      initialize();
    }

    void Polygon::add_vertex(Vertex *vertex) {
      vertex->polygons.push_back(this);
      vertices.push_back(vertex);
    }

    void Polygon::initialize() {
      for (int i = 0; i < vertices.size(); ++i) {
        auto next = (i + 1) % vertices.size();
        auto existing = vertices[i]->get_edge(vertices[next]);
        if (existing != nullptr) {
          edges.push_back(existing);
          existing->polygons.push_back(this);
        }
        else {
          edges.push_back(new Edge(vertices[i], vertices[next]));
        }
      }

      if (vertices.size() <= 4) {
        uvs = new vec2[vertices.size()];
        for (int i = 0; i < vertices.size(); ++i) {

        }
      }
      else {
        uvs = NULL;
      }

    }

    Polygon::~Polygon() {
      if (uvs)
        delete uvs;
    }

    void Polygon::remove(Mesh *mesh) {
      for (int i = vertices.size() - 1; i >= 0; --i) {
        auto vertex = vertices[i];
        vector_remove(vertex->polygons, this);
      }

      vertices.empty();

      for (int i = edges.size() - 1; i >= 0; --i) {
        auto edge = edges[i];
        vector_remove(edge->polygons, this);
      }

      edges.empty();
    }
  }
}