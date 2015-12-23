#include "sculptor/geometry.h"
#include <algorithm>

using namespace std;

namespace sculptor {
  namespace geometry {
    Mesh::Mesh() {

    }

//    Mesh_Pointer Mesh::get_shared() {
//      return std::make_shared<Mesh>(&this);
//    }

    Vertex *Mesh::add_vertex(Vertex *vertex) {
      vertices.push_back(vertex);
      vertex->meshes.push_back(this);
      return vertex;
    }

    Vertex *Mesh::add_vertex(vec3 vector) {
      return add_vertex(new Vertex(vector));
    }

    Polygon *Mesh::add_polygon(Polygon *polygon) {
      polygons.push_back(polygon);
      polygon->meshes.push_back(this);

      for (auto vertex : polygon->vertices) {
        if (std::find(vertices.begin(), vertices.end(), vertex) != vertices.end())
          continue;

        add_vertex(vertex);
      }

      for (auto edge : polygon->edges) {
        if (std::find(edges.begin(), edges.end(), edge) != edges.end())
          continue;

//        add_edge(edge);
      }
    }

    template<typename Iterator>
    Polygon *Mesh::add_polygon(Iterator vertices) {
      auto polygon = new Polygon(vertices);
      add_polygon(polygon);
    }
  }
}