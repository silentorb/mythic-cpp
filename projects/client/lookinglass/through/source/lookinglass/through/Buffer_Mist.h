#pragma once

#include "Mist.h"
#include "Data_Buffer.h"

namespace lookinglass {
  namespace through {

    template<typename T>
    class MYTHIC_EXPORT Buffer_Mist : public Mist<T> {
        Data_Buffer buffer;
    public:
        virtual void initialize(const unsigned int id, const char *name, const std::map<string, Program *> &programs) {
          buffer.initialize(id, sizeof(T));
        }

        virtual void update(T *data) {
          buffer.update(data);
        }
    };
  }
}