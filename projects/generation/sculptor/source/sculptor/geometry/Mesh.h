#pragma once

#include "declarations.h"

namespace sculptor {
  namespace geometry {
    class Mesh {
    public:
        Mesh();
        vector<Vertex *> vertices;
        vector<Polygon *> polygons;
        vector<Edge *> edges;

        Vertex *add_vertex(Vertex *vertex);
//        ::get_shared::Mesh_Pointer get_shared();
        Vertex *add_vertex(vec3 vertex);

        template<typename Iterator>
        Polygon *add_polygon(Iterator vertices);
        Polygon *add_polygon(Polygon *polygon);
        Polygon *add_polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
    };

  }
}