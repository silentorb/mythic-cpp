#include "selection.h"
#include "sculptor/geometry/Mesh.h"
#include "operations.h"
#include <sculptor/geometry/Polygon.h>
#include "sculptor/geometry/Edge.h"

namespace sculptor_old {

  namespace selecting {
    Basic_Mesh *const get_mesh(const Selection &selection) {
      if (selection.size() == 0)
        return nullptr;

      return selection[0]->get_mesh();
    }

    Selection clone(const Selection &selection, const mat4 offset) {
      if (selection.size() == 0)
        return Selection();

      auto mesh = get_mesh(selection);
      Selection result(selection.size());
      for (int i = 0; i < selection.size(); i++) {
        auto new_vector = operations::transform(selection[i]->get_position(), offset);
        result[i] = mesh->add_vertex(new_vector);
      }

      auto polygons = get_polygons(selection);
      for (auto polygon:polygons) {
        auto indices = polygon->get_indices(selection);
        auto new_polygon = new Polygon(from_indices(result, indices));
        mesh->add_polygon(new_polygon);
      }

      return result;
    }

    const vector<Polygon *> get_polygons(const Selection &selection) {
      vector<Polygon *> polygons;
      auto mesh = get_mesh(selection);

      for (auto polygon: mesh->polygons) {
        if (contains_polygon(selection, *polygon)) {
          polygons.push_back(polygon);
        }
      }

      return polygons;
    }

    const vector<Edge *> get_edges(const Selection &selection) {
      vector<Edge *> polygons;
      auto mesh = get_mesh(selection);

      for (auto edge: mesh->get_edges()) {
        if (contains_edge(selection, *edge)) {
          polygons.push_back(edge);
        }
      }

      return polygons;
    }

    bool edge_polygon_count(const Selection &selection, Edge &edge) {
      auto count = 0;
      for (auto polygon: edge.polygons) {
        if (contains_polygon(selection, *polygon))
          ++count;
      }

      return count;
    }

    const vector<Edge *> get_edge_edges(const Selection &selection) {
      vector<Edge *> polygons;
      auto mesh = get_mesh(selection);

      for (auto edge: mesh->get_edges()) {
        if (contains_edge(selection, *edge) && edge_polygon_count(selection, *edge) == 1) {
          polygons.push_back(edge);
        }
      }

      return polygons;
    }

    bool contains_polygon(const Selection &selection, const Polygon &polygon) {
      for (auto vertex: polygon.vertices) {
        if (!contains_vertex(selection, *vertex))
          return false;
      }

      return true;
    }

    bool contains_edge(const Selection &selection, const Edge &edge) {
      for (auto vertex: edge.vertices) {
        if (!contains_vertex(selection, *vertex))
          return false;
      }

      return true;
    }

    Selection from_indices(const Selection &selection, const vector<int> &indices) {
      Selection result(indices.size());
      for (int i = 0; i < indices.size(); ++i) {
        result[i] = selection[indices[i]];
      }

      return result;
    }

    bool contains_vertex(const Selection &selection, const Vertex &vertex) {
      for (auto item: selection) {
        if (item == &vertex)
          return true;
      }

      return false;
    }

    Selection slice(const Selection &selection, int start, int end) {
      return Selection(selection.begin() + start, selection.begin() + end);
    }

    int get_vertex_index(const Selection &selection, Vertex &vertex) {
      return std::find(selection.begin(), selection.end(), &vertex) - selection.begin();
    }
  }
}