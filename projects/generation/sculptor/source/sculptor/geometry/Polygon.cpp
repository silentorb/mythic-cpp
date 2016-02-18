#include <vectoring/utility.h>
#include "sculptor/geometry.h"

namespace sculptor {
  namespace geometry {

    Polygon::Polygon(initializer_list<Vertex *> source) {
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
      initialize();
    }

    Polygon::Polygon(Vertex *first, Vertex *second, Vertex *third) {
      add_vertex(first);
      add_vertex(second);
      add_vertex(third);
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
        for (int i = 0; i < vertices.size(); ++i) {

        }
      }
    }

    Polygon::~Polygon() {
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

    vec3 Polygon::calculate_normal() const {
      vec3 first = vertices[0]->get_position(),
        second = vertices[1]->get_position(),
        third = vertices[2]->get_position();
      auto result = glm::normalize(glm::cross(first - second, third - second));
      auto a = get_center() + result;
      auto b = get_center() - result;
      return a.length() > b.length() ? result : -result;
    }

//    void Polygon::add_normal(const vec3 normal) {
//      normals.push_back(normal);
//    }

    void Polygon::set_data(const string &name, float *values, int count) {
      data.insert(Vertex_Data::value_type(name, vector<float>(vertices.size() * count)));
//      data[name].assign(values, values + count);
      float *entry = data[name].data();
      for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < count; ++j) {
          *entry++ = values[j];
        }
      }
    }

    vec3 Polygon::get_center() const {
      vec3 result = vec3(0);
      for (auto vertex: vertices) {
        result += vertex->get_position();
      }

      return result / (float) vertices.size();
    }
  }
}
