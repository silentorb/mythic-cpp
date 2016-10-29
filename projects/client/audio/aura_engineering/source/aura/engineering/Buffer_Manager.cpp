#include "Buffer_Manager.h"

namespace aura {
  namespace engineering {


    Buffer_Manager::Buffer_Manager(int element_size, int starting_capacity) :
      element_size(element_size) {

      if (starting_capacity > 0) {
        data = unique_ptr<unsigned char>(new unsigned char[capacity * element_size]);
      }
    }

    unsigned char *Buffer_Manager::push() {
      ++size;
      if (size > capacity) {
        auto old_capacity = capacity;
        capacity = capacity == 0
                   ? 1
                   : capacity * 2;

        auto new_buffer = new unsigned char[capacity * element_size];
        if (old_capacity > 0)
          memcpy(new_buffer, data.get(), old_capacity * element_size);

        data = unique_ptr<unsigned char>(new_buffer);
      }

      return data.get() + (size - 1) * element_size;
    }

    void Buffer_Manager::pop() {
      --size;
    }

  }
}