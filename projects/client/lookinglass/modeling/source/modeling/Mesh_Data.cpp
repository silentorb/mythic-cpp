#include <lookinglass/glow/Capabilities.h>
#include "Mesh_Data.h"
#include "lookinglass/glow.h"
#include "Vertex_Schema.h"

namespace modeling {
  Mesh_Data::Mesh_Data(Mesh_Data_Generator generator,
                       Vertex_Schema &vertex_schema, bool support_lines, bool has_opacity) :
    generator(generator), vertex_schema(vertex_schema), support_lines{support_lines}, _has_opacity(has_opacity) {
    load();
  }

  Mesh_Data::~Mesh_Data() {
    free();
  }

  int get_polygon_index_count(int point_count) {
    return (point_count - 2) * 3;
  }

  unsigned short *convert_to_indices(int &index_count, Mesh_Export &data, int vertex_size) {
    index_count = 0;
    {
      for (int i = 0; i < data.polygon_count; ++i) {
        int polygon_index_count = get_polygon_index_count(data.counts.get()[i]);
        index_count += polygon_index_count;
      }
    }

    auto result = new unsigned short[index_count];
    auto indices = result;
    auto offset = 0;
    {
      for (int i = 0; i < data.polygon_count; ++i) {
        auto original_count = data.counts.get()[i];
        int polygon_index_count = get_polygon_index_count(original_count);
        for (int j = 0; j < original_count - 2; ++j) {
          *indices++ = offset;
          *indices++ = offset + j + 1;
          *indices++ = offset + j + 2;
        }

        offset += original_count;
      }
    }

    return result;
  }

  void Mesh_Data::load() {
    Mesh_Export data;
    generator(data);
    polygon_count = data.polygon_count;
    int vertex_count = data.vertex_count;
//    float *vertices = data.vertices.get();
    shared_ptr<unsigned short> indices;
    this->_has_opacity = data.has_opacity;

    if (!glow::Capabilities::multidraw() && !support_lines) {
      indices = shared_ptr<unsigned short>(convert_to_indices(index_count, data, vertex_schema.get_vertex_size()));
      glGenBuffers(1, &ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * index_count, indices.get(), GL_STATIC_DRAW);
    }
    else {
      offsets = data.offsets;
      counts = data.counts;
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glow::check_error("binding vbo");

    glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), data.vertices.get(), GL_STATIC_DRAW);
    glow::check_error("binding vbo buffer data");

    vao = vertex_schema.create_vao();
  }

  void Mesh_Data::free() {
    if (!vao)
      return;

    if (ebo) {
      glDeleteBuffers(1, &ebo);
      ebo = 0;
    }

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
  }
}
