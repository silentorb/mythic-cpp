#pragma once

#include <vector>
#include <cstdlib>

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Dynamic_Delay {
        std::vector<Signal_Type> buffer;

    public:
        Dynamic_Delay(size_t size) {
          set_size(size);
        }

        void update(const Signal_Type &value) {
          std::move(buffer.begin(), buffer.end() - 1, buffer.begin() + 1);
          buffer[0] = value;
        }

        void set_size(size_t value) {
          buffer.resize(value);
        }

        const std::vector<Signal_Type> &get_buffer() const {
          return buffer;
        }

        const Signal_Type &get_last() const {
          return buffer[buffer.size() - 1];
        }

        size_t get_size() const {
          return buffer.size();
        }

        const Signal_Type &operator[](size_t index) const{
          return buffer[index];
        }
    };
  }
}