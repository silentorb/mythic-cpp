#pragma once

#include "dllexport.h"

namespace aura {
  class Buffer_Manager;

  class Conductor;

  class MYTHIC_EXPORT Buffer {
      unsigned char *data;
      Buffer_Manager &manager;
      const int _size;

  public:
      Buffer(Conductor &conductor);

      ~Buffer();

      int size() {
        return _size;
      }

      unsigned char *get() const {
        return data;
      }
  };

}

