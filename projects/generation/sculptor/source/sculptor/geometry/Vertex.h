#pragma once
#include "dllexport.h"

namespace sculptor {
  namespace geometry {
    class MYTHIC_EXPORT Vertex {
    public:
        Vertex(vec3 tvec3);

        template<typename Iterator>
        Vertex(vec3 vector, Iterator new_meshes);
        vector<Mesh *> meshes;
        vector<Polygon *> polygons;
        vector<Edge *> edges;
        vec3 position;
        Edge *get_edge(Vertex *other);
    };
  }
}