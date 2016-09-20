#include <utility.h>
#include <iostream>
#include "Vertex_Buffer.h"
#include "glow.h"
#include "glow_gl.h"

namespace modeling {

  Vertex_Buffer::Vertex_Buffer(const Vertex_Schema &vertex_schema, Vertex_Generator generator) :
    vertex_schema(vertex_schema), generator(generator) {

  }

  Vertex_Buffer::~Vertex_Buffer() {
    release();

  }

  void Vertex_Buffer::load() {
    if (generator) {
      int vertex_count = 0;
      auto data = generator(vertex_count);
      load(vertex_count, data);
    }
  }

  void Vertex_Buffer::load(int new_vertex_count, float *data) {
//    std::cout << "  vb: " << (void *) this << " vbo: " << vbo << " count: " << new_vertex_count << std::endl;

    if (!vbo) {
      glGenBuffers(1, &vbo);
      glow::set_array_buffer(vbo);
      glow::check_error("binding vbo");

      vertex_count = new_vertex_count;
      glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), data, GL_STATIC_DRAW);
      glow::check_error("binding vbo buffer data");
        
//        glDeleteBuffers(1, &vbo);
//        vbo = 0;
//        glow::set_array_buffer(0);
//        
//        glGenBuffers(1, &vbo);
//        glow::set_array_buffer(vbo);
//        glow::check_error("binding vbo");
//        
//        vertex_count = new_vertex_count;
//        glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), data, GL_STATIC_DRAW);
//        glow::check_error("binding vbo buffer data");
        
        vao = vertex_schema.create_vao();
    }
    else {
    glow::set_array_buffer(vbo);
      if (!is_dynamic) {
        is_dynamic = true;
        vertex_count = new_vertex_count;
        glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), data, GL_DYNAMIC_DRAW);
        glow::check_error("binding vbo buffer data");
      }
      else {
        if (vertex_count < new_vertex_count) {
          vertex_count *= 2;
          if (vertex_count < new_vertex_count)
            vertex_count += new_vertex_count;

          glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_schema.get_vertex_size(), nullptr, GL_DYNAMIC_DRAW);
        }
        glBufferSubData(GL_ARRAY_BUFFER, 0, new_vertex_count * vertex_schema.get_vertex_size(), data);
      }
    }
  }

  void Vertex_Buffer::release() {
    if (!vao)
      return;
//    std::cout << "- vb: " << (void *) this << " vbo: " << vbo << std::endl;
      
      // There seems to be a multi-platform hardware bug where deleting the currently bound
      // vbo and then generating a new one results in corrupting the new vbo.
      if (glow::get_array_buffer() == vbo)
          glow::set_array_buffer(0);
      
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    vao = 0;
    vbo = 0;
  }

  void Vertex_Buffer::activate() {
    glow::check_error("binding");
    glBindVertexArray(vao);
    glow::check_error("bound");
  }

  void Vertex_Buffer::draw_points(int count) {
    activate();
    glDrawArrays(GL_POINTS, 0, count);
  }
}
