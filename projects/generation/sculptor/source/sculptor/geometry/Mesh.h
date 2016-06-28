#pragma once

#include "dllexport.h"

#include "declarations.h"
//#include "Polygon.h"
#include "sculptor/operations/selection.h"

namespace sculptor {
  namespace geometry {

    class MYTHIC_EXPORT Mesh {
    private:

    public:
        Mesh();
        ~Mesh();
        vector<Vertex *> vertices;
        vector<Polygon *> polygons;
        vector<Edge *> edges;

        Vertex *add_vertex(Vertex *vertex);
        Vertex *add_vertex(vec3 vertex);

//        template<typename Iterator>
//        Polygon *add_polygon(Iterator vertices);
        Polygon *add_polygon(Polygon *polygon);
        Polygon *add_polygon(initializer_list<vec3> vectors);
        Polygon *add_polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
        Polygon *add_polygon(vec3 first, vec3 second, vec3 third);
//        Polygon *add_polygon(vec3 first, vec3 second, vec3 third, vec3 fourth);

        const vector<Edge *> &get_edges() const {
          return edges;
        }

        vec3 get_center() const;

        unsigned long get_vertex_count() const {
          return vertices.size();
        }

        Vertex &get_vertex(int index) const {
          return *vertices[index];
        }

        int get_vertex_index(Vertex & vertex)const;

        void add_vertices(vec3 *points, int count);

        Vertex **get_vertex_data() {
          return vertices.data();
        }

        Polygon *add_polygon(std::initializer_list<Vertex *> vertices);
//        Polygon *add_polygon(std::initializer_list<Vertex *> vertices) {
//          auto polygon = new Polygon(vertices);
//          add_polygon(polygon);
//        }

        Selection select() const {
//          auto buffer = new Vertex *[vertices.size()];
//          memcpy(buffer, vertices.data(), vertices.size() * sizeof(Vertex*));
//          return Selection(buffer, vertices.size(), true);
          return Selection(vertices);
        }

        Selection select(std::initializer_list<int> indices) const {
          Selection buffer(indices.size());
          int i = 0;
          for(auto index : indices) {
            buffer[i++] = vertices[index];
          }
          return buffer;
        }
    };

  }
}