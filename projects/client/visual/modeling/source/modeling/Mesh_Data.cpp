#include <glow/Capabilities.h>
#include "Mesh_Data.h"
#include "glow.h"
#include "glow_gl.h"

namespace modeling {

  Mesh_Data::Mesh_Data(Mesh_Data_Generator generator,
                       const Vertex_Schema &vertex_schema, bool support_lines, bool has_opacity) :
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

    if (!glow::Capabilities::get_instance().multidraw() && !support_lines) {
      indices = shared_ptr<unsigned short>(
        convert_to_indices(index_count, data, vertex_buffer.get_vertex_schema().get_vertex_size()));
      element_buffer.initialize(index_count, indices.get());
    }
    else {
      offsets = data.offsets;
      counts = data.counts;
    }

    vertex_buffer.load(vertex_count, data.vertices.get());
      element_buffer.activate();
            glow::set_vertex_array(0);
  }

  void Mesh_Data::release() {
    vertex_buffer.release();
    element_buffer.release();
  }
  
  int convert_draw_method(modeling::Draw_Method mode) {
    switch (mode) {
      case (Draw_Method::triangles):
        return GL_TRIANGLES;
        break;
      case (Draw_Method::triangle_fan):
        return GL_TRIANGLE_FAN;
        break;
      case (Draw_Method::line_loop):
        return GL_LINE_LOOP;
        break;
      case (Draw_Method::line_strip):
        return GL_LINE_STRIP;
        break;
      case (Draw_Method::lines):
        return GL_LINES;
        break;
      case (Draw_Method::points):
        return GL_POINTS;
        break;

      default:
        throw std::runtime_error("Not supported.");
    }
  }
  
  void Mesh_Data::render(Draw_Method draw_method) {
    vertex_buffer.activate();

    auto mode = convert_draw_method(draw_method);
//    auto mode = draw_method == Draw_Method::triangle_fan
//                ? GL_TRIANGLE_FAN
//                : GL_LINE_STRIP;

    if (glow::Capabilities::get_instance().multidraw()) {
      // The preprocessor is needed or this will fail to compile on some platforms.
#ifdef glMultiDrawArrays
      glMultiDrawArrays(mode, get_offsets(), get_counts(), get_polygon_count());
#endif
    }
    else {
      if (draw_method == Draw_Method::line_loop || supports_lines()) {
        for (int i = 0; i < get_polygon_count(); ++i) {
          glDrawArrays(mode, get_offsets()[i], get_counts()[i]);
        }
      }
      else {
        //element_buffer.activate();
        glDrawElements(GL_TRIANGLES, get_index_count(), GL_UNSIGNED_SHORT, nullptr);
      }
    }

      glow::set_vertex_array(0);
    glow::check_error("drawing mesh");
  }
}
