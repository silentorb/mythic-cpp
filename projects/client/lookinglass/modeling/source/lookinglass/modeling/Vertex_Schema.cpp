#include "Vertex_Schema.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  namespace modeling {

    int get_sum(vector<Vertex_Attribute> attributes) {
      int total = 0;
      for (auto &attribute: attributes) {
        total += attribute.count;
      }
      return total;
    }

    Vertex_Schema::Vertex_Schema(initializer_list<Vertex_Attribute> attributes_initializer) :
      attributes(attributes_initializer) {
      field_count = get_sum(attributes);
      vertex_size = field_count * sizeof(float);

//      for (auto &attribute: attributes) {
//        attribute.stride = vertex_size;
//      }
    }

    Vertex_Schema::Vertex_Schema(initializer_list<int> attributes_initializer) {
      for (auto a : attributes_initializer) {
        attributes.push_back(Vertex_Attribute("", a));
      }
      field_count = get_sum(attributes);
      vertex_size = field_count * sizeof(float);

//      for (auto &attribute: attributes) {
//        attribute.stride = vertex_size;
//      }
    }

    unsigned int Vertex_Schema::create_vao() const {
      unsigned int schema = 0;
      int offset = 0;
      glGenVertexArrays(1, &schema);
      glBindVertexArray(schema);
      glow::check_error("creating vao");

      const int stride = 0;

      for (int i = 0; i < attributes.size(); ++i) {
        auto &attribute = attributes[i];
        glVertexAttribPointer(i, attribute.count, GL_FLOAT, false, stride, i == 0 ? 0 : (void *) offset);
        glow::check_error("creating vertex attribute");

        glEnableVertexAttribArray(i);
        glow::check_error("enabling vertex attribute");

        offset += attribute.count * sizeof(float);
      }
    }

  }
}