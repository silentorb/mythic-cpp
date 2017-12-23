#pragma once


#include "sculptor/geometry/declarations.h"
#include "sculptor/geometry/Vertex.h"
#include <vector>

using namespace std;

namespace sculptor_old {
  namespace geometry {
    class Basic_Mesh;
  }
  using namespace geometry;

  typedef vector<Vertex *> Selection;

  namespace selecting {
    Basic_Mesh *const get_mesh(const Selection &selection);
    Selection clone(const Selection &selection, const mat4 offset);
    const vector<Polygon *> get_polygons(const Selection &selection);
    bool contains_polygon(const Selection &selection, const Polygon &polygon);
    Selection from_indices(const Selection &selection, const vector<int> &indices);
    bool contains_vertex(const Selection &selection, const Vertex &vertex);
    Selection slice(const Selection &selection, int start, int end);
    bool contains_edge(const Selection &selection, const Edge &edge);
    const vector<Edge *> get_edges(const Selection &selection);
    const vector<Edge *> get_edge_edges(const Selection &selection);
    int get_vertex_index(const Selection &selection, Vertex &vertex);
  }
//  class Selection {
//  public:
//      virtual int size() const = 0;
//      virtual Vertex **data() const = 0;
//      virtual Vertex *get(int index) const = 0;
//  };
  /*
  class Selection {
      Vertex *const *vertices;
      int count;
      bool owner;

      static Vertex **copy(const Selection& selection) {
        auto buffer = new Vertex*[selection.size()];
        memcpy(buffer, selection.data(), selection.size() * sizeof(Vertex*));
        return buffer;
      }

  public:
      Selection() : vertices(nullptr), count(0), owner(false) { }

      Selection(Vertex **vertices, int count, bool owner = false)
        : vertices(vertices), count(count), owner(owner) { }

      Selection(const vector<Vertex *> &vertices)
        : vertices(vertices.data()), count(vertices.size()), owner(false) { }

      Selection(const Selection &source) : vertices(copy(source)), count(source.size()), owner(true)
      { }

      ~Selection() {
        if (owner)
          delete vertices;
      }

      int size() const {
        return count;
      }

      Vertex *const *data() const {
        return vertices;
      }

      Vertex *get(int index) const {
        return vertices[index];
      }

      Mesh *const get_mesh() const;

      Selection slice(int start, int end) const {
        auto new_count = end - start;
        auto result = new Vertex *[new_count];
        memcpy(result, vertices + start, new_count * sizeof(Vertex *));
        return Selection(result, new_count);
      }

      Vertex *operator[](const int index) const {
        return vertices[index];
      }

      Selection clone(const mat4 offset) const;

      bool contains_vertex(const Vertex &vertex) const {
        for (int i = 0; i < count; ++i) {
          if (vertices[i] == &vertex)
            return true;
        }

        return false;
      }

      bool contains_polygon(const Polygon &polygon) const;
      const vector<Polygon *> get_polygons() const;

      Selection from_indices(const vector<int> &indices) const{
        auto buffer = new Vertex *[indices.size()];
        for (int i = 0; i < indices.size(); ++i) {
          buffer[i] = vertices[indices[i]];
        }
        return Selection(buffer, indices.size());
      }
  };
  */
}