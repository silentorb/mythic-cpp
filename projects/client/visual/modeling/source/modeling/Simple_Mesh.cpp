#include "Simple_Mesh.h"
#include "shading/Vertex_Schema.h"
#include "glow.h"
#include "glow_gl.h"
#include "Draw_Method.h"

namespace modeling {
  Simple_Mesh::Simple_Mesh(float *data, int vertex_count, const Vertex_Schema &vertex_schema)
    : data(data), vertex_count(vertex_count), vertex_schema(vertex_schema) {
    load();
  }

  Simple_Mesh::Simple_Mesh(const Vertex_Schema &vertex_schema) :
    vertex_schema(vertex_schema) {
    vertex_count = 0;
  }

  Simple_Mesh::~Simple_Mesh() {
    release();
//    delete data;
  }

  void Simple_Mesh::render(Draw_Method mode) {
    glBindVertexArray(vao);
    glDrawArrays(mode == Draw_Method::triangles ? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, vertex_count);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, vertex_count);
  }

  void Simple_Mesh::load() {
    glGenBuffers(1, &vbo);
    glow::set_array_buffer(vbo);
    glow::check_error("Error storing mesh data.");

    if (vertex_count > 0) {
      glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size() * sizeof(float), data,
                   GL_STATIC_DRAW);
      glow::check_error("Error storing mesh data.");
    }

    vao = vertex_schema.create_vao();
  }

  void Simple_Mesh::load(float *data, int vertex_count) {
    this->data = data;
    this->vertex_count = vertex_count;

    glow::set_array_buffer(vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size() * sizeof(float), data,
                 GL_STATIC_DRAW);

    glow::check_error("Error storing mesh data.");
  }

  void Simple_Mesh::release() {
    if (!vao)
      return;

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
  }

}