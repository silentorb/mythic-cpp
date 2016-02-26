#pragma once

#include "dllexport.h"

#include "declarations.h"
#include <map>
#include <string>

namespace sculptor {
  namespace geometry {

    typedef map<const string, vector<float>> Vertex_Data;

    class MYTHIC_EXPORT Polygon {
    private:
        void initialize();
        void add_vertex(Vertex *vertex);
        Vertex_Data data;
        vec3 normal;

    public:
        vector<Mesh *> meshes;
        vector<Vertex *> vertices;
        vector<Edge *> edges;
//        vector<vec3> normals;
//        vector<vec2> uvs;

//        template<typename Iterator>
//        Polygon(Iterator vertices);
        Polygon(initializer_list<Vertex *>);
        Polygon(const Selection &selection);
        Polygon(Vertex *first, Vertex *second, Vertex *third, Vertex *fourth);
        Polygon(Vertex *first, Vertex *second, Vertex *third);
        ~Polygon();

//        Polygon(initializer_list<Vertex *> source) {
//          for (Vertex *vertex : source) {
//            add_vertex(vertex);
//          }
//
//          initialize();
//        }

        void remove();

        vec3 calculate_normal() const;
//        void add_normal(const vec3 normal);

        void set_data(const string &name, float *data, int count);

        float *get_data(const string &name) {
          if (!data.count(name))
            return nullptr;

          return data[name].data();
        }

        float *get_data(const string &name, int index) {
          if (!data.count(name))
            return nullptr;

          float *values = data[name].data();
          auto step = data[name].size() / vertices.size();
          return values + index * step;
        }

        const vec3 &get_normal() const {
          return normal;
        }

        void set_normal(const vec3 &normal) {
          Polygon::normal = normal;
        }

        vec3 get_center() const;

        const vector<int> get_indices(const Selection & selection) const;

        void flip();
    };
  }
}
