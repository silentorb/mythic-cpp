#include "sculptor/geometry.h"
#include "vectoring/utility.h"

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
        if (!vector_contains(vertices, vertex))
          add_vertex(vertex);
      }

      for (auto edge : polygon->edges) {
        if (!vector_contains(edges, edge)){
          edges.push_back(edge);
          edge->meshes.push_back(this);
        }
//          add_edge(edge);
      }

      return polygon;
    }

    template<typename Iterator>
    Polygon *Mesh::add_polygon(Iterator vertices) {
      auto polygon = new Polygon(vertices);
      add_polygon(polygon);
    }

    Polygon *Mesh::add_polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth) {
      auto polygon = new Polygon(first, second, third, fourth);
      add_polygon(polygon);
			return polygon;
    }

    Polygon *Mesh::add_polygon(vec3 first, vec3 second, vec3 third, vec3 fourth) {
      auto polygon = new Polygon(
        add_vertex(first),
        add_vertex(second),
        add_vertex(third),
        add_vertex(fourth));
      add_polygon(polygon);
			return polygon;
    }
  }
}