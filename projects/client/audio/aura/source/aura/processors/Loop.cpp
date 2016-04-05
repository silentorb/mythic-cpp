#include "Loop.h"
#include <cmath>
#include <iostream>
#include "aura/engineer/Engineer.h"

namespace aura {

  Loop::Loop(Engineer & conductor, double frequency) :
	frequency(frequency),
  sample_rate(conductor.get_sample_rate()) {
    increment = frequency / sample_rate;
  }

  float Loop::next() {
    auto old = position;
    position = fmod(position + increment, 1.0);
    if (frequency < 1) {

      if (position < old)
        std::cout << "Looped" << std::endl;
    }

    return position;
  }

  float Loop::next(int cycles) {
    position = fmod(position + increment * cycles, 1.0);
    return position;
  }
}