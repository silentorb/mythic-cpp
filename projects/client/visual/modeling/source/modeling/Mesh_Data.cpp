#include <glow/Capabilities.h>
#include "Mesh_Data.h"
#include "glow.h"
#include "Vertex_Buffer.h"
#include "glow_gl.h"

namespace modeling {
  Mesh_Data::Mesh_Data(Mesh_Data_Generator generator,
                       Vertex_Schema &vertex_schema, bool support_lines, bool has_opacity) :
    generator(generator), vertex_buffer(vertex_schema), support_lines{support_lines}, _has_opacity(has_opacity) {
    load();
  }

  Mesh_Data::~Mesh_Data() {
    release();
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
    unsigned short offset = 0;
    {
      for (int i = 0; i < data.polygon_count; ++i) {
        auto original_count = data.counts.get()[i];
        int polygon_index_count = get_polygon_index_count(original_count);
        for (unsigned short j = 0; j < original_count - 2; ++j) {
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
      indices = shared_ptr<unsigned short>(
        convert_to_indices(index_count, data, vertex_buffer.get_vertex_schema().get_vertex_size()));
      glGenBuffers(1, &ebo);
      if (!ebo)
        throw runtime_error("Unable to create mesh buffer.");

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * index_count, indices.get(), GL_STATIC_DRAW);
    }
    else {
      offsets = data.offsets;
      counts = data.counts;
    }

    vertex_buffer.load(vertex_count, data.vertices.get());
  }

  void Mesh_Data::release() {
    vertex_buffer.release();

    if (ebo) {
      glDeleteBuffers(1, &ebo);
      ebo = 0;
    }
  }

  void Mesh_Data::draw(Draw_Method draw_method) {
    vertex_buffer.activate();

    auto mode = draw_method == Draw_Method::triangles
                ? GL_TRIANGLE_FAN
                : GL_LINE_STRIP;

    if (glow::Capabilities::multidraw()) {
      // The preprocessor is needed or this will fail to compile on some platforms.
#ifdef glMultiDrawArrays
      glMultiDrawArrays(mode, get_offsets(), get_counts(), get_polygon_count());
#endif
    }
    else {
      if (draw_method == Draw_Method::lines || supports_lines()) {
        for (int i = 0; i < get_polygon_count(); ++i) {
          glDrawArrays(mode, get_offsets()[i], get_counts()[i]);
        }
      }
      else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, get_ebo());
        glDrawElements(GL_TRIANGLES, get_index_count(), GL_UNSIGNED_SHORT, nullptr);
      }
    }

    glow::check_error("drawing mesh");
  }
}
