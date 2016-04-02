#include "Buffer.h"
#include "Conductor.h"

namespace aura {


  Buffer::Buffer(Conductor &conductor) :
    manager(conductor.get_buffer_manager()),
    _size(conductor.get_buffer_size()) {
    data = manager.push();
  }

  Buffer::~Buffer() {
    manager.pop();
  }

}

