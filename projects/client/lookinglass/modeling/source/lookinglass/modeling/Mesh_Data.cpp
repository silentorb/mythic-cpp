#include "Mesh_Data.h"
#include "lookinglass/glow.h"
#include "Vertex_Schema.h"


namespace lookinglass {
  namespace modeling {
    Mesh_Data::Mesh_Data(int polygon_count, int vertex_count, float *vertices, int *offsets, int *counts,
                         const Vertex_Schema &vertex_schema)
      : polygon_count(
      polygon_count), vertex_count(vertex_count), vertices(vertices),
        offsets(offsets), counts(counts), vertex_schema(vertex_schema) {
      load();
    }

    Mesh_Data::~Mesh_Data() {
      free();
    }

    void Mesh_Data::register_mesh(const Vertex_Schema &schema) {
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glow::check_error("binding vbo");

      glBufferData(GL_ARRAY_BUFFER, vertex_count * schema.get_vertex_size(), vertices, GL_STATIC_DRAW);
      glow::check_error("binding vbo buffer data");

      vao = schema.create_vao();
    }

    void Mesh_Data::free() {
      if (!vao)
        return;

      glDeleteBuffers(1, &vao);
      glDeleteBuffers(1, &vbo);
      vao = 0;
    }

    void Mesh_Data::load() {
      register_mesh(vertex_schema);
    }
  }
}