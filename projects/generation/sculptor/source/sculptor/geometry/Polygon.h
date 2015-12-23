#pragma once
#include "declarations.h"

namespace sculptor {
  namespace geometry {
    class Polygon {
    public:
        vector<Mesh *> meshes;
        vector<Vertex *> vertices;
        vector<Edge *> edges;
        vec2 *uvs;

        template<typename Iterator>
        Polygon(Iterator vertices);
        ~Polygon();

        void remove(Mesh* mesh);
    };
  }
}