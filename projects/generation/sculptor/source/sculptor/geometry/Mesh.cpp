#include "sculptor/geometry.h"
//#include "vectoring/utility.h"

using namespace std;

namespace sculptor {
  namespace geometry {
    Mesh::Mesh() {

    }

    Mesh::~Mesh() {
      for (auto polygon : polygons) {
        delete polygon;
      }

      for (auto vertex : vertices) {
        delete vertex;
      }

      for (auto edge: edges) {
        delete edge;
      }
    }

    Vertex *Mesh::add_vertex(Vertex *vertex) {
      vertices.push_back(vertex);
      vertex->set_mesh(this);
      return vertex;
    }

    Vertex *Mesh::add_vertex(vec3 vector) {
      return add_vertex(new Vertex(vector));
    }

    Polygon *Mesh::add_polygon(Polygon *polygon) {
      polygons.push_back(polygon);
      polygon->meshes.push_back(this);

      for (auto vertex : polygon->vertices) {
        if (vertex->get_mesh() != this)
          add_vertex(vertex);
      }

      for (auto edge : polygon->edges) {
        if (edge->get_mesh() != this) {
          edges.push_back(edge);
          edge->set_mesh(this);
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

    Polygon *Mesh::add_polygon(initializer_list<vec3> vectors) {
      Selection selection;
      for (auto &v: vectors) {
        auto vertex = add_vertex(v);
        selection.push_back(vertex);
      }
      auto polygon = new Polygon(selection);
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

    int Mesh::get_vertex_index(Vertex &vertex) const {
      return (int) (std::find(vertices.begin(), vertices.end(), &vertex) - vertices.begin());
    }
  }
}