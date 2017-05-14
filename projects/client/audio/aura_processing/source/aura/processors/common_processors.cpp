#include "common_processors.h"
#include <cmath>
#include <vector>
#include <stdexcept>

namespace aura {

  static std::vector<float> db_buffer;

  float to_db_internal(float value) {
    auto base = 10;
    return (std::pow(base, value) - 1) / (base - 1);
  }

  void initialize_db() {
    unsigned long range = 4000;
    db_buffer.resize(range);
    for (long i = 0; i < range; ++i) {
      float position = 2 * (float) i / (float) range;
      db_buffer[i] = to_db_internal(position);
    }
  }

  float to_db(float value) {
//    return pow(value, 2);
//    if (value == 1)
//      return 1;

    if (value < 0 || value >= 2)
      return to_db_internal(value);
//      throw std::runtime_error("Invalid db range.");

    float initial = 0.5f * value * db_buffer.size();
    unsigned int index = (unsigned int)initial;
//    float diff = initial - (float)index;

    return db_buffer[index];
  }
}