#include "Loop.h"
#include <cmath>
#include <iostream>
#include "aura/engineer/Engineer.h"

namespace aura {

  Loop::Loop(Engineer &conductor, double frequency) :
//    frequency(frequency),
    sample_rate(conductor.get_sample_rate()) {
    increment = frequency / sample_rate;
  }

  float Loop::next() {
    auto old = position;
    position += increment;
    if (position > 1)
      position = fmod(position + increment, 1.0);

    return (float) position;
  }

//  float Loop::next(int cycles) {
////    position = fmod(position + increment * cycles, 1.0);
//    position += increment * cycles;
//    if (position > 1) {
//      position = fmod(position, 1.0);
//
//    }
//    return position;
//  }

  float Loop::next(bool &looped) {
//    position = fmod(position + increment * cycles, 1.0);
    position += increment;
    if (position > 1) {
      position = fmod(position, 1.0);
      looped = true;
    }
    else {
      looped = false;
    }

//    auto old = position;
//    position = fmod(position + increment, 1.0);
//    looped = false;
//    if (frequency < 1) {
//
//      if (position < old)
//        looped = true;
////        std::cout << "Looped" << std::endl;
//    }

    return (float) position;
  }
}