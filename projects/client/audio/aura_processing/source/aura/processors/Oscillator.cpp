#include <cmath>
#include <math/utility.h>
#include "Oscillator.h"
#include "aura/engineering/Engineer.h"
#include "signal_generators.h"

namespace aura {

  Oscillator::Oscillator(engineering::Engineer &engineer, float frequency, const Loop_Function &operation) :
    loop(engineer.get_sample_rate(), frequency),
    operation(operation) {}

  Oscillator::Oscillator(engineering::Engineer &engineer, float frequency) :
    Oscillator(engineer, frequency, generate::sine) {

  }

  Oscillator::Oscillator(unsigned int sample_rate, float frequency, const Loop_Function &operation) :
    loop(sample_rate, frequency),
    operation(operation) {}

  Oscillator::Oscillator(unsigned int sample_rate, float frequency) :
    Oscillator(sample_rate, frequency, generate::sine) {

  }
}