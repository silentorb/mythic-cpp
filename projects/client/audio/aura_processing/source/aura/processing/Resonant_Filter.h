#pragma once

#include <aura/engineering/Engineer.h>
#include <math/utility.h>
#include <cmath>
#include "Fixed_Delay.h"
#include "Filter_Base.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Resonant_Filter : public Resonant_Filter_Base<Signal_Type> {
        Fixed_Delay<float, 2> original_buffer;
        Fixed_Delay<float, 2> output_buffer;
        float a0, a2, b1, b2;

        void pre_calculate() {
          auto arc = 2 * Pi * this->frequency / this->sample_rate;
          auto bandwidth = this->frequency / this->Q;
          b2 = std::exp(-2 * Pi * bandwidth / this->sample_rate);
          b1 = (-4 * b2) / (1 + b2) * cos(arc);
          a0 = 1 - sqrt(b2);
          a2 = -a0;
          this->changed = false;
        }

    public:
        Resonant_Filter(unsigned int sample_rate, float Q) :
          Resonant_Filter_Base<Signal_Type>(sample_rate, Q) {}

        float operator()(float input) {
          if (this->changed)
            pre_calculate();

          auto output = a0 * input + a2 * original_buffer[1] - b1 * output_buffer[0] - b2 * output_buffer[1];

          original_buffer.update(input);
          output_buffer.update(output);
          return output;
        }
    };
  }
}