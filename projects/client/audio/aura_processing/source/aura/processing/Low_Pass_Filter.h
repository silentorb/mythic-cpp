#pragma once

#include <aura/engineering/Engineer.h>
#include <math/utility.h>
#include <c++/cmath>
#include "Fixed_Delay_Buffer.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Low_Pass_Filter {
        Fixed_Delay_Buffer<float, 2> original_buffer;
        Fixed_Delay_Buffer<float, 2> output_buffer;
        const unsigned int sample_rate;
        float frequency;
        float Q;
        float a0, a2, b1, b2;
        bool changed = true;

        void pre_calculate() {
          auto arc = 2 * Pi * frequency / sample_rate;
          auto bandwidth = frequency / Q;
          b2 = std::exp(-2 * Pi * bandwidth / sample_rate);
          b1 = (-4 * b2) / (1 + b2) * cos(arc);
          a0 = 1 - sqrt(b2);
          a2 = -a0;
          changed = false;
        }

    public:
        Low_Pass_Filter(unsigned int sample_rate) :
          sample_rate(sample_rate) {}

        float operator()(float input) {
          if (changed)
            pre_calculate();

          auto output = a0 * input + a2 * original_buffer[1] - b1 * output_buffer[0] - b2 * output_buffer[1];

          original_buffer.update(input);
          output_buffer.update(output);
          return output;
        }

        void set_frequency(float value) {
          if (frequency == value)
            return;

          frequency = value;
          changed = true;
        }

        void set_Q(float value) {
          if (Q == value)
            return;

          Q = value;
          changed = true;
        }
    };
  }
}