#include <cmath>
#include <math/utility.h>
#include "Oscillator.h"
#include "aura/conductor/Conductor.h"

namespace aura {

  Oscillator::Oscillator(Conductor &conductor, float frequency, Loop_Function operation) :
    loop(conductor.get_sample_rate(), frequency), conductor(conductor),
    operation(operation) { }

//  void Oscillator::update(Buffer & buffer) {
//    auto data = buffer.get();
//    for (int i = 0; i < buffer.size(); ++i) {
//      data[i] = sin(loop.next() * 2 * Pi);
//      if (conductor.get_channel_count() == 2)
//        data[++i] = data[i - 1];
//    }
//  }

  float Oscillator::update() {
    return sin(loop.next() * 2 * Pi);
  }

}