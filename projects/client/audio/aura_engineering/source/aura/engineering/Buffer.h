#pragma once

#include "commoner/dllexport.h"

namespace aura {
  namespace engineering {

    class Buffer_Manager;

    class Engineer;

    class MYTHIC_EXPORT Buffer {
        float *data;
        Buffer_Manager *manager;
        const int _size;

    public:
        Buffer(Engineer &engineer);
        Buffer(float *data, int buffer_size);
        Buffer(unsigned char *data, int buffer_size);

        ~Buffer();

        int size() {
          return _size;
        }

        float *get() const {
          return data;
        }
    };
  }
}

