#pragma once
#include "dllexport.h"

#include "declarations.h"

namespace sculptor {
  namespace geometry {
    class MYTHIC_EXPORT Mesh {
		private:
			vector<Edge *> edges;

    public:
        Mesh();
        vector<Vertex *> vertices;
        vector<Polygon *> polygons;

        Vertex *add_vertex(Vertex *vertex);
//        ::get_shared::Mesh_Pointer get_shared();
        Vertex *add_vertex(vec3 vertex);

        template<typename Iterator>
        Polygon *add_polygon(Iterator vertices);
        Polygon *add_polygon(Polygon *polygon);
        Polygon *add_polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
        Polygon *add_polygon(vec3 first, vec3 second, vec3 third, vec3 fourth);

        const vector<Edge *> &get_edges() const {
          return edges;
        }
    };

  }
}