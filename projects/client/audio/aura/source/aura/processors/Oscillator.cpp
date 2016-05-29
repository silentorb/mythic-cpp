#include <cmath>
#include <math/utility.h>
#include "Oscillator.h"
#include "aura/engineer/Engineer.h"

namespace aura {

  Oscillator::Oscillator(Engineer &engineer, float frequency, Loop_Function operation) :
    loop(engineer.get_sample_rate(), frequency), engineer(engineer),
    operation(operation) { }

  Oscillator::Oscillator(Engineer &engineer, const Generator frequency_generator, Loop_Function operation) :
    loop(engineer.get_sample_rate()), engineer(engineer),
    operation(operation), frequency_generator(frequency_generator) { }

  float Oscillator::operator()() {
    if (frequency_generator)
      loop.set_frequency(frequency_generator());

    return operation(loop.next());
  }

}