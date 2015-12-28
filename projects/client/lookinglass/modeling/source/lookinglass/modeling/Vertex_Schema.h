#pragma once

#include <vector>
#include "Vertex_Attribute.h"

using namespace std;

namespace lookinglass {
  namespace modeling {
    class Vertex_Schema {
    private:
        vector<Vertex_Attribute> attributes;
        int vertex_size;
        int field_count;

    public:
        Vertex_Schema(initializer_list<Vertex_Attribute> attributes);
        Vertex_Schema(initializer_list<int> attributes_initializer);
//        Vertex_Schema(Vertex_Schema &&source) :
//          attributes(source.attributes), vertex_size(source.vertex_size), field_count(source.field_count) { }

        unsigned int create_vao() const;

        int get_vertex_size() const {
          return vertex_size;
        }
    };
  }
}