#include <cmath>
#include <math/utility.h>
#include "Oscillator.h"
#include "aura/engineer/Engineer.h"

namespace aura {

  Oscillator::Oscillator(Engineer &engineer, float frequency, Loop_Function operation) :
    loop(engineer.get_sample_rate(), frequency), engineer(engineer),
    operation(operation) { }

//  void Oscillator::update(Buffer & buffer) {
//    auto data = buffer.get();
//    for (int i = 0; i < buffer.size(); ++i) {
//      data[i] = sin(loop.next() * 2 * Pi);
//      if (engineer.get_channel_count() == 2)
//        data[++i] = data[i - 1];
//    }
//  }

  float Oscillator::update() {
//    return sin(loop.next() * 2 * Pi);
    return operation(loop.next());
  }

}