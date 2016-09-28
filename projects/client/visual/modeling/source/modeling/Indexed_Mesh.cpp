#include "Indexed_Mesh.h"
#include "glow.h"
#include "glow_gl.h"

namespace modeling {

  Indexed_Mesh::Indexed_Mesh(const Vertex_Schema &vertex_schema) :
    vertex_buffer(vertex_schema) {

  }

  void Indexed_Mesh::render(Draw_Method mode) {
    vertex_buffer.activate();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer.get_id());
    glDrawElements(GL_TRIANGLES, vertex_buffer.get_vertex_count(), GL_UNSIGNED_SHORT, nullptr);

    glow::check_error("drawing mesh");
  }
}