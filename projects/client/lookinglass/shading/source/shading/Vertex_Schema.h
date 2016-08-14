#pragma once

#include "commoner/dllexport.h"

#include <vector>
#include "Vertex_Attribute.h"

using namespace std;

namespace shading {

  class MYTHIC_EXPORT Vertex_Schema {
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

      int get_attribute_count() const {
        return attributes.size();
      }

      const Vertex_Attribute &get_attribute(int index) const {
        return attributes[index];
      }

      const vector<Vertex_Attribute> &get_attributes() const {
        return attributes;
      }
  };
}
