#pragma once

#include <vector>
#include <cstdlib>
#include <memory.h>

namespace aura {
  namespace processing {

    template<typename Signal_Type, size_t Size>
    class Fixed_Delay_Buffer {
        Signal_Type buffer[Size];

    public:
        Fixed_Delay_Buffer() {
          memset(&buffer, 0, Size * sizeof(Signal_Type));
        }

        void update(const Signal_Type &value) {
          memcpy(&buffer[1], &buffer[0], (Size - 1) * sizeof(Signal_Type));
          buffer[0] = value;
        }

        const Signal_Type &get_last() const {
          return buffer[Size - 1];
        }

        const Signal_Type &operator[](size_t index) const {
          return buffer[index];
        }
    };
  }
}