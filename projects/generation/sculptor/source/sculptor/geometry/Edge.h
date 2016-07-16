#pragma once

#include "dllexport.h"
#include <vectoring/utility.h>

namespace sculptor {
  namespace geometry {
    class MYTHIC_EXPORT Edge {

        void find_polygons();

    public:
        Edge(Vertex *first, Vertex *second);
//        vector<Mesh *> meshes;
        Basic_Mesh *mesh = nullptr;
        Vertex *vertices[2];
        vector<Polygon *> polygons;
        bool contains(Vertex *vertex);
        void get_ordered_points(Vertex *points[2]);

//        template<typename Iterator>
//        static void get_vertices(Iterator &edges, vector<Vertex *> vertices);
//
//        template<typename Iterator>
//        static void get_polygons(Iterator &edges, vector<Polygon *> polygons);

        template<typename Iterator>
        static void get_vertices(Iterator &edges, vector<Vertex *> &vertices) {
          for (auto edge: edges) {
            for (auto vertex: edge->vertices) {
              if (!vector_contains(vertices, vertex))
                vertices.push_back(vertex);
            }
          }
        }

        template<typename Iterator>
        static void get_polygons(Iterator &edges, vector<Polygon *> &polygons) {
          for (auto edge: edges) {
            for (auto polygon: edge->polygons) {
              if (!vector_contains(polygons, polygon))
                polygons.push_back(polygon);
            }
          }
        }

        Basic_Mesh *get_mesh() const {
          return mesh;
        }

        void set_mesh(Basic_Mesh *mesh) {
          Edge::mesh = mesh;
        }

        Vertex *get_other_vertex(Vertex *vertex);
    };
  }
}