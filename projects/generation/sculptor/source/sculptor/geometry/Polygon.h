#pragma once
#include "dllexport.h"

#include "declarations.h"

namespace sculptor {
  namespace geometry {
    class MYTHIC_EXPORT Polygon {
    private:
        void initialize();
        void add_vertex(Vertex *vertex);

    public:
        vector<Mesh *> meshes;
        vector<Vertex *> vertices;
        vector<Edge *> edges;
        vec2 *uvs;

        template<typename Iterator>
        Polygon(Iterator vertices);
        Polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
        ~Polygon();

        void remove(Mesh *mesh);
    };
  }
}