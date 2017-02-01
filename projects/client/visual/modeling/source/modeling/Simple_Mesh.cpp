#include "Simple_Mesh.h"
#include "shading/Vertex_Schema.h"
#include "glow.h"
#include "glow_gl.h"
#include "Draw_Method.h"

namespace modeling {
  Simple_Mesh::Simple_Mesh(float *data, int vertex_count, const Vertex_Schema &vertex_schema)
    : data(data), vertex_buffer(vertex_schema) {
    vertex_buffer.load(vertex_count, data);
    load();
  }

  Simple_Mesh::Simple_Mesh(const Vertex_Schema &vertex_schema) :
    vertex_buffer(vertex_schema) {
//    initialize();
  }

  Simple_Mesh::~Simple_Mesh() {
    release();
//    delete data;
  }

//  void Simple_Mesh::initialize() {
//    glGenBuffers(1, &vbo);
//    glow::set_array_buffer(vbo);
//    glow::check_error("Error storing mesh data.");
//    vao = vertex_schema.create_vao();
//  }

  void Simple_Mesh::render(Draw_Method mode) {
    if (vertex_buffer.get_vertex_count() == 0)
      return;

    vertex_buffer.activate();
    GLenum _mode;
    switch (mode) {
      case (Draw_Method::triangles):
        _mode = GL_TRIANGLES;
        break;
      case (Draw_Method::triangle_fan):
        _mode = GL_TRIANGLE_FAN;
        break;
      case (Draw_Method::line_loop):
        _mode = GL_LINE_LOOP;
        break;
      case (Draw_Method::line_strip):
        _mode = GL_LINE_STRIP;
        break;
      case (Draw_Method::lines):
        _mode = GL_LINES;
        break;
      case (Draw_Method::points):
        _mode = GL_POINTS;
        break;
    }
    glDrawArrays(_mode, 0, vertex_buffer.get_vertex_count());
  }

  void Simple_Mesh::load() {
//    initialize();

    vertex_buffer.load(vertex_buffer.get_vertex_count(), data);
//    if (vertex_buffer.get_vertex_count() > 0) {
//      glBufferData(GL_ARRAY_BUFFER, vertex_buffer.get_vertex_count() * vertex_buffer.get_vertex_schema().get_vertex_size(), data,
//                   GL_STATIC_DRAW);
//      glow::check_error("Error storing mesh data.");
//    }
  }

  void Simple_Mesh::replace(float *data, int vertex_count) {
    vertex_buffer.load(vertex_count, data);
//    glow::set_array_buffer(vbo);
//    glow::set_vertex_array(vao);
//    if (this->vertex_count == 0) {
//      if (vertex_count == 0)
//        return;
//
//      glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), data,
//                   GL_DYNAMIC_DRAW);
//    }
//    else {
//      glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * vertex_schema.get_vertex_size(), data);
//    }
//    this->data = data;
//    this->vertex_count = vertex_count;
//
//    glow::check_error("Error storing mesh data.");
  }


  void Simple_Mesh::release() {
    vertex_buffer.release();
//    if (!vao)
//      return;
//
//    // There seems to be a multi-platform hardware bug where deleting the currently bound
//    // vbo and then generating a new one results in corrupting the new vbo.
//    if (glow::get_array_buffer() == vbo)
//      glow::set_array_buffer(0);
//
//    if (glow::get_vertex_array() == vao)
//      glow::set_vertex_array(0);
//
//#ifdef ANDROID
//      glDeleteBuffers(1, &vao);
//#else
//    glDeleteVertexArrays(1, &vao);
//#endif
//
//    glDeleteBuffers(1, &vbo);
//    vao = 0;
  }
}