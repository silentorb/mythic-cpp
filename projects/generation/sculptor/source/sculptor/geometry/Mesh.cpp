#include "sculptor/geometry.h"
//#include "vectoring/utility.h"

using namespace std;

namespace sculptor {
  namespace geometry {
    Mesh::Mesh() {

    }

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
        if (!vector_contains(edges, edge)) {
          edges.push_back(edge);
          edge->meshes.push_back(this);
        }
//          add_edge(edge);
      }

      polygon->set_normal(polygon->calculate_normal());
      return polygon;
    }

//    template<typename Iterator>
//    Polygon *Mesh::add_polygon(Iterator vertices) {
//      auto polygon = new Polygon(vertices);
//      add_polygon(polygon);
//    }

    Polygon *Mesh::add_polygon(std::initializer_list<Vertex *> vertices) {
      auto polygon = new Polygon(vertices);
      add_polygon(polygon);
      return polygon;
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

    Polygon *Mesh::add_polygon(vec3 first, vec3 second, vec3 third) {
      auto polygon = new Polygon(
        add_vertex(first),
        add_vertex(second),
        add_vertex(third));
      add_polygon(polygon);
      return polygon;
    }

    vec3 Mesh::get_center() const {
      vec3 result = vec3(0);
      for (auto vertex: vertices) {
        result += vertex->get_position();
      }

      return result / (float) vertices.size();
    }

    void Mesh::add_vertices(vec3 *points, int count) {
			for (size_t i = 0; i < count; i++) {
				add_vertex(points[i]);
			}
    }
  }
}