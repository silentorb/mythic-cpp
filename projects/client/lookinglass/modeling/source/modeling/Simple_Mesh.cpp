#include "Simple_Mesh.h"
#include "Vertex_Schema.h"
#include "lookinglass/glow.h"

using namespace lookinglass;

namespace modeling {
  Simple_Mesh::Simple_Mesh(float *data, int vertex_count, const modeling::Vertex_Schema &vertex_schema)
    : data(data), vertex_count(vertex_count), vertex_schema(vertex_schema) {
    load();
  }

  Simple_Mesh::Simple_Mesh(const Vertex_Schema &vertex_schema) :
    vertex_schema(vertex_schema) {
    vertex_count = 0;
  }

  Simple_Mesh::~Simple_Mesh() {
    free();
    delete data;
  }

  void Simple_Mesh::render(bool solid) {
    glBindVertexArray(vao);
    glDrawArrays(solid ? GL_TRIANGLE_FAN : GL_LINE_STRIP, 0, solid ? vertex_count : vertex_count + 3);
  }

  void Simple_Mesh::load() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size() * sizeof(float), data,
                 GL_STATIC_DRAW);

    glow::check_error("Error storing mesh data.");
  }

  void Simple_Mesh::free() {
    if (!vao)
      return;

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
  }

}