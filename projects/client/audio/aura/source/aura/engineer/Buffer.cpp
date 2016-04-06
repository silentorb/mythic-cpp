#include "Buffer.h"
#include "Engineer.h"

namespace aura {


  Buffer::Buffer(Engineer &engineer) :
    manager(&engineer.get_buffer_manager()),
    _size(engineer.get_buffer_byte_size() / sizeof(float)) {
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

