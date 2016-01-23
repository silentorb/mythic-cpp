#include "Simple_Mesh.h"
#include "Vertex_Schema.h"
#include "lookinglass/glow.h"

using namespace lookinglass;

namespace modeling {
  Simple_Mesh::Simple_Mesh(float *data, int vertex_count, modeling::Vertex_Schema &vertex_schema)
    : data(data), vertex_count(vertex_count), vertex_schema(vertex_schema) {
    load();
  }

  Simple_Mesh::~Simple_Mesh() {
    free();
    delete data;
  }

  void Simple_Mesh::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertex_count + 2);
  }

  void Simple_Mesh::load() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glow::check_error("Error storing mesh data.");

    glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), data, GL_STATIC_DRAW);
    glow::check_error("Error storing mesh data.");

    vao = vertex_schema.create_vao();
  }

  void Simple_Mesh::free() {
    if (!vao)
      return;

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
  }

}