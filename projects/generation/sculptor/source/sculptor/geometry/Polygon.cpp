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

    Polygon::Polygon(const Selection &selection) {
      vertices.reserve(selection.size());
      for (int i = 0; i < selection.size(); ++i) {
        add_vertex(selection[i]);
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
    }

    void Polygon::initialize_edges() {
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
    }

    Polygon::~Polygon() {
    }

    void Polygon::remove() {
      for (int i = (int) vertices.size() - 1; i >= 0; --i) {
        auto vertex = vertices[i];
        vector_remove(vertex->polygons, this);
      }

      vertices.empty();

      for (int i = (int) edges.size() - 1; i >= 0; --i) {
        auto edge = edges[i];
        vector_remove(edge->polygons, this);
      }

      edges.empty();

      for (auto mesh : meshes) {
        vector_remove(mesh->polygons, this);
      }
    }

    vec3 Polygon::calculate_normal() const {
      vec3 first = vertices[0]->get_position(),
        second = vertices[1]->get_position(),
        third = vertices[2]->get_position();

      // The order of cross arguments is essential in this case.
      // calculate_normal is relying on the order of vertices
      // to have the cross product face in the right direction.
      return glm::normalize(glm::cross(third - second, first - second));
    }

    void Polygon::set_data(int id, float *values, int step, int count) {
      auto entry = get_entry(id);
      if (!entry) {
        data.push_back(Vertex_Data());
        entry = &data[data.size() - 1];
        entry->id = id;
      }
      entry->values.reserve(vertices.size() * count);
      float *entry_data = entry->values.data();
      for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < count; ++j) {
          *entry_data++ = values[j];
        }
        values += step;
      }
    }

    vec3 Polygon::get_center() const {
      vec3 result = vec3(0);
      for (auto vertex: vertices) {
        result += vertex->get_position();
      }

      return result / (float) vertices.size();
    }

    const vector<int> Polygon::get_indices(const Selection &selection) const {
      vector<int> result(vertices.size());
      for (int i = 0; i < vertices.size(); ++i) {
        result[i] = selecting::get_vertex_index(selection, *vertices[i]);
      }

      return result;
    }

    void Polygon::flip() {
      std::reverse(vertices.begin(), vertices.end());
    }
  }

  vector<Edge *> Polygon::get_edges() {
    if (edges.size() == 0)
      initialize_edges();

    return edges;
  }

}
