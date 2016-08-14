#pragma once

#include "commoner/dllexport.h"

#include "sculptor/geometry.h"
#include "operations.h"
#include <vectoring/utility.h>

using namespace sculptor::geometry;

namespace sculptor {
  namespace operations {
//    template<typename Iterator>
//    void extrude(Iterator &edges, mat4 &offset, bool fill = false);
    template<typename Iterator>
    void extrude(const Iterator &edges, const mat4 &offset, bool fill = false) {

      Basic_Mesh *mesh = vector_first(edges)->get_mesh();
      auto count = edges.size();

      vector<Edge *> original_edges;
      for (auto &edge: edges) {
        original_edges.push_back(edge);
      }

      vector<Polygon *> polygons;
      if (fill) {
        Edge::get_polygons(edges, polygons);
      }

      Selection original_vertices;
      Edge::get_vertices(edges, original_vertices);

      Selection new_vertices;
      for (auto &original_vertex: original_vertices) {
        auto temp = offset * vec4(original_vertex->get_position(), 1);
        auto new_vector = vec3(temp);
        auto new_vertex = mesh->add_vertex(new_vector);
        new_vertices.push_back(new_vertex);
      }

      operations:: fill_gap(original_vertices, new_vertices);

      if (fill) {
        for (auto &polygon: polygons) {
          mesh->add_polygon(
            new_vertices[vector_index(original_vertices, polygon->vertices[3])],
            new_vertices[vector_index(original_vertices, polygon->vertices[2])],
            new_vertices[vector_index(original_vertices, polygon->vertices[1])],
            new_vertices[vector_index(original_vertices, polygon->vertices[0])]
          );
        }
      }
    }
  }
}