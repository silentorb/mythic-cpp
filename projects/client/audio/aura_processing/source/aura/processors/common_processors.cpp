#include "common_processors.h"
#include <cmath>
#include <vector>

namespace aura {

  static std::vector<float> db_buffer;

  float to_db_internal(float value) {
    auto base = 10;
    return (std::pow(base, value) - 1) / (base - 1);
  }

  void initialize_db() {
    unsigned long range = 2000;
    db_buffer.resize(range);
    for (long i = 0; i < range; ++i) {
      float position = (float) i / (float) range;
      db_buffer[i] = to_db_internal(position);
    }
  }

  float to_db(float value) {
//    return pow(value, 2);
    if (value < 0 || value >= 1)
      return to_db_internal(value);

    float initial = (value * db_buffer.size());
    unsigned int index = (unsigned int)initial;
//    float diff = initial - (float)index;

    return db_buffer[index];
  }
}