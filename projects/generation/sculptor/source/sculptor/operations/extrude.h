#pragma once
#include "dllexport.h"

#include "sculptor/geometry.h"
#include <vectoring/utility.h>

using namespace sculptor::geometry;

namespace sculptor {
  namespace operations {
//    template<typename Iterator>
//    void extrude(Iterator &edges, mat4 &offset, bool fill = false);
    template<typename Iterator>
    void extrude(const Iterator &edges, mat4 &offset, bool fill = false) {

      Mesh *mesh = vector_first(vector_first(edges)->meshes);
      auto count = edges.size();

      vector<Edge *> original_edges;
      for (auto &edge: edges) {
        original_edges.push_back(edge);
      }

      vector<Polygon *> polygons;
      if (fill) {
        Edge::get_polygons(edges, polygons);
      }

      vector<Vertex *> original_vertices;
      Edge::get_vertices(edges, original_vertices);

      vector<Vertex *> new_vertices;
      for (auto &original_vertex: original_vertices) {
				auto temp = offset * vec4(original_vertex->get_position(), 1);
				auto new_vector = vec3(temp);
				auto new_vertex = mesh->add_vertex(new_vector);
        new_vertices.push_back(new_vertex);
      }

      for (auto &edge : original_edges) {
        Vertex *points[2];
        edge->get_ordered_points(points);
        auto a = vector_index(original_vertices, points[0]);
        auto b = vector_index(original_vertices, points[1]);
        if (edge->vertices[0] != points[0]) {
          auto c = a;
          a = b;
          b = c;
        }
        mesh->add_polygon(
          points[1],
          points[0],
          new_vertices[a],
          new_vertices[b]
        );
      }

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