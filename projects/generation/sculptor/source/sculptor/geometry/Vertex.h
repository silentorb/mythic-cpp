#pragma once

#include "dllexport.h"

using namespace glm;
using namespace std;

namespace sculptor {
  namespace geometry {
    class MYTHIC_EXPORT Vertex : no_copy {
        vec3 position;

    public:
        Vertex(vec3 tvec3);
        ~Vertex();

        template<typename Iterator>
        Vertex(vec3 vector, Iterator new_meshes);
        vector<Mesh *> meshes;
        vector<Polygon *> polygons;
        vector<Edge *> edges;
        Edge *get_edge(Vertex *other);

        const vec3 &get_position() const {
          return position;
        }

        void set_position(const vec3 &position) {
          this->position = position;
        }
    };
  }
}