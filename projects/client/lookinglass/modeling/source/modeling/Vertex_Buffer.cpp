#include <lookinglass/utility.h>
#include "Vertex_Buffer.h"
#include "lookinglass/glow.h"

namespace modeling {

  Vertex_Buffer::Vertex_Buffer(const Vertex_Schema &vertex_schema, Vertex_Generator generator) :
    vertex_schema(vertex_schema), generator(generator) {

  }

  Vertex_Buffer::~Vertex_Buffer() {
    release();

  }

  void Vertex_Buffer::load() {
    if (generator) {
      int vertex_count;
      auto data = generator(vertex_count);
      load(vertex_count, data);
    }
  }

  void Vertex_Buffer::load(int vertex_count, float *data) {

    if (!vbo) {
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glow::check_error("binding vbo");
    }
    else {
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }

    glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), data, GL_STATIC_DRAW);
    glow::check_error("binding vbo buffer data");

    if (!vao) {
      vao = vertex_schema.create_vao();
    }
  }

  void Vertex_Buffer::release() {
    if (!vao)
      return;

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
    vbo = 0;
  }

  void Vertex_Buffer::activate() {
    glBindVertexArray(vao);
  }

  void Vertex_Buffer::draw_points(int count) {
    activate();
    glDrawArrays(GL_POINTS, 0, count);
  }
}