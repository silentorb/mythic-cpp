#include "Mesh_Data.h"
#include "lookinglass/glow.h"
#include "Vertex_Schema.h"

using namespace lookinglass;

namespace modeling {
  Mesh_Data::Mesh_Data(Mesh_Data_Generator generator,
                       Vertex_Schema &vertex_schema) :
    generator(generator), vertex_schema(vertex_schema) {
    load();
  }

  Mesh_Data::~Mesh_Data() {
    free();
  }

  void Mesh_Data::load() {
    Mesh_Export data;
    generator(data);
    offsets = data.offsets;
    counts = data.counts;
    polygon_count = data.polygon_count;
    vertex_count = data.vertex_count;

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

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
  }
}
