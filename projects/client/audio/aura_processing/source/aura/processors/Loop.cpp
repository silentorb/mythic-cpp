#include "Loop.h"
#include <cmath>
#include <iostream>
#include "aura/engineering/Engineer.h"

namespace aura {

  using namespace engineering;

//  Loop::Loop(Engineer &engineer, double frequency) :
////    frequency(frequency),
//    sample_rate(engineer.get_sample_rate()) {
//    increment = frequency / sample_rate;
//    position = -increment;
//  }

  void Loop::update() {
//    ++step;
//    auto position2 = increment * step;
//    if (position2 > 1) {
//      step = step % (long)std::round(1 / increment);
//      return (float)increment * step;
//    }

//    return (float)position2;
//    auto old = position;
    position += increment;
    if (position >= 1) {
      position -= 1;
      if (position > 1)
        position = fmod(position + increment, 1.0);
    }

//    return old;
  }


  void Loop::update(bool &looped) {
    position += increment;
    if (position >= 1) {
      if (position -= 1 > 1)
        position = fmod(position, 1.0);

      looped = true;
    }
    else {
      looped = false;
    }
  }
}