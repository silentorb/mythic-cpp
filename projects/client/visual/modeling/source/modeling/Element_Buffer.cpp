#include "Element_Buffer.h"
#include "glow.h"
#include "glow_gl.h"
#include <stdexcept>

namespace modeling {

  void Element_Buffer::initialize(int index_count, unsigned short *indices) {
    glGenBuffers(1, &id);
    if (!id)
      throw std::runtime_error("Unable to create mesh buffer.");

    activate();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * index_count, indices, GL_STATIC_DRAW);
  }

  void Element_Buffer::activate() {
    glow::set_element_array_buffer(id);
  }

  Element_Buffer::~Element_Buffer() {
    release();
  }

  void Element_Buffer::release() {
    if (id) {
      glDeleteBuffers(1, &id);
      id = 0;
    }
  }
}
