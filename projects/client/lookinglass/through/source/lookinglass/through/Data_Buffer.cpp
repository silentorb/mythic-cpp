#include "Data_Buffer.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  namespace through {

    Data_Buffer::Data_Buffer(unsigned int index, unsigned int size) {
      initialize(index, size);
    }

    void Data_Buffer::initialize(unsigned int index, unsigned int size) {
#ifndef __ANDROID__
      this->index = index;
      this->size = size;
      glGenBuffers(1, &id);
      glBindBuffer(GL_UNIFORM_BUFFER, id);
      glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
      glow::check_error("creating uniform buffer");
#endif
    }

    Data_Buffer::~Data_Buffer() {
      glDeleteBuffers(1, &id);
    }

    void Data_Buffer::update(void *data) {
#ifndef __ANDROID__
      glBindBuffer(GL_UNIFORM_BUFFER, id);
      glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
#endif
    }

  }
}
