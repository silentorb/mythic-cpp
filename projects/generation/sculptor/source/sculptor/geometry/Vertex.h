#pragma once

#include "commoner/dllexport.h"

using namespace glm;
using namespace std;

namespace sculptor_old {
  namespace geometry {
    class MYTHIC_EXPORT Vertex : no_copy {
        vec3 position;

    public:
        Vertex(vec3 tvec3);
        ~Vertex();

        template<typename Iterator>
        Vertex(vec3 vector, Iterator new_meshes);
//        vector<Mesh *> meshes;
        Basic_Mesh *mesh;
        vector<Polygon *> polygons;
        vector<Edge *> edges;
        Edge *get_edge(Vertex *other);

        const vec3 &get_position() const {
          return position;
        }

        void set_position(const vec3 &position) {
          this->position = position;
        }

        Basic_Mesh *get_mesh() const {
          return mesh;
        }

        void set_mesh(Basic_Mesh *mesh) {
          this->mesh = mesh;
        }

        void reserve_polygons(int size) {
          polygons.reserve(size);
        }
    };
  }
}