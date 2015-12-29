#pragma once
#include "dllexport.h"
#include <vectoring/utility.h>

namespace sculptor {
  namespace geometry {
    class MYTHIC_EXPORT Edge {
    public:
        Edge(Vertex *first, Vertex *second);
        vector<Mesh *> meshes;
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
    };
  }
}