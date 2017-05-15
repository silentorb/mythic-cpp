#pragma once

#include "Loop.h"

namespace aura {
  namespace processing {

    class Oscillator {
        constexpr static float DEFAULT_FREQUENCY = 440;
        Loop loop;
        const Loop_Function operation;

    public:

        Oscillator(unsigned int sample_rate, float frequency, const Loop_Function &operation);

        Oscillator(unsigned int sample_rate, const Loop_Function &operation) : Oscillator(sample_rate,
                                                                                          DEFAULT_FREQUENCY,
                                                                                          operation) {}

//        Oscillator(unsigned int sample_rate, float frequency = DEFAULT_FREQUENCY);

        float get_frequency() const {
          return loop.get_frequency();
        }

        void set_frequency(float frequency) {
          loop.set_frequency(frequency);
        }

        float operator()() {
            auto old = loop.get_next_float();
            loop.update();
          return old;
        }

        float operator()(float frequency) {
          set_frequency(frequency);
            auto old = loop.get_next_float();
            loop.update();
            return old;
        }

    };
  }
}