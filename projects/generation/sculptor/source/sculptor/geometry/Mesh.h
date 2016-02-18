#pragma once

#include "dllexport.h"

#include "declarations.h"
//#include "Polygon.h"

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
        Vertex *add_vertex(vec3 vertex);

//        template<typename Iterator>
//        Polygon *add_polygon(Iterator vertices);
        Polygon *add_polygon(Polygon *polygon);
        Polygon *add_polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
        Polygon *add_polygon(vec3 first, vec3 second, vec3 third);
        Polygon *add_polygon(vec3 first, vec3 second, vec3 third, vec3 fourth);

        const vector<Edge *> &get_edges() const {
          return edges;
        }

        vec3 get_center() const;

        int get_vertex_count() const {
          return vertices.size();
        }

        Vertex &get_vertex(int index) const {
          return *vertices[index];
        }

        void add_vertices(vec3 *points, int count);

        Vertex **get_vertex_data() {
          return vertices.data();
        }

        Polygon *add_polygon(std::initializer_list<Vertex*> vertices);
//        Polygon *add_polygon(std::initializer_list<Vertex *> vertices) {
//          auto polygon = new Polygon(vertices);
//          add_polygon(polygon);
//        }
    };

  }
}