#include "Buffer.h"
#include "Conductor.h"

namespace aura {


  Buffer::Buffer(Conductor &conductor) :
    manager(&conductor.get_buffer_manager()),
    _size(conductor.get_buffer_byte_size() / sizeof(float)) {
    data = (float*)manager->push();
  }

  Buffer::Buffer(float *data, int buffer_size) :
    manager(nullptr),
    _size(buffer_size),
    data(data) { }

  Buffer::Buffer(unsigned char *data, int buffer_size) :
    manager(nullptr),
    _size(buffer_size / sizeof(float)),
    data((float*)data) { }

  Buffer::~Buffer() {
    if (manager)
      manager->pop();
  }

}

