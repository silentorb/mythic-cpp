#pragma once

#include <aura/engineering/Buffer.h>
#include "Loop.h"

namespace aura {

  namespace engineering {
    class Engineer;
  }

  class Oscillator {
      constexpr static float DEFAULT_FREQUENCY = 440;
      Loop loop;
      const Loop_Function operation;

  public:
      Oscillator(engineering::Engineer &engineer, float frequency, const Loop_Function &operation);

      Oscillator(engineering::Engineer &engineer, const Loop_Function &operation) : Oscillator(engineer, DEFAULT_FREQUENCY,
                                                                                               operation) {}

      Oscillator(engineering::Engineer &engineer, float frequency = DEFAULT_FREQUENCY);

      Oscillator(unsigned int sample_rate, float frequency, const Loop_Function &operation);

      Oscillator(unsigned int sample_rate, const Loop_Function &operation) : Oscillator(sample_rate, DEFAULT_FREQUENCY,
                                                                                               operation) {}

      Oscillator(unsigned int sample_rate, float frequency = DEFAULT_FREQUENCY);
      float get_frequency() const {
        return loop.get_frequency();
      }

      void set_frequency(float frequency) {
        loop.set_frequency(frequency);
      }

      float operator()() {
        return operation(loop());
      }

      float operator()(float frequency) {
        set_frequency(frequency);
        return operation(loop());
      }

  };

//  typedef std::function<Oscillator *(engineering::Engineer &, float, Loop_Function)> Oscillator_Generator;
}