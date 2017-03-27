#pragma once

#include <aura/processing/Filter_Base.h>
#include <math/utility.h>
#include <cmath>
#include <aura/processing/utility.h>

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Gain_Filter : public Resonant_Filter_Base<Signal_Type> {
        Fixed_Delay<Signal_Type, 2> original_buffer;
        Fixed_Delay<Signal_Type, 2> output_buffer;
        Second_Order_Mix_Calculations<Signal_Type> calculation;
        float gain;

        void pre_calculate() {
          auto arc = 2 * Pi * this->frequency / this->sample_rate;
          auto m = gain * 4;
          auto L = 4 / (1 + m);
          auto k = L * tan(arc / (2 * this->Q));
          auto B = 0.5 * (1 - k) / (1 + k);
          auto y = (0.5 + B) * cos(arc);

          calculation.a0 = 0.5 - B;
          calculation.a1 = 0;
          calculation.a2 = -(0.5 - B);
          calculation.b1 = -2 * y;
          calculation.b2 = 2 * B;
          calculation.c = m - 1;
          calculation.d = 1;
        }

    public:
        Gain_Filter(unsigned int sample_rate, float Q) :
          Resonant_Filter_Base<Signal_Type>(sample_rate, Q) {}

        Signal_Type operator()(Signal_Type input) {
          if (this->changed) {
            pre_calculate();
            this->changed = false;
          }

          auto processed = calculation.process(input, original_buffer, output_buffer);
          auto output = calculation.c * processed
                        + calculation.d * input;

          original_buffer.update(input);
          output_buffer.update(processed);
          return output;
        }

        void set_gain(float value) {
          gain = value;
        }
    };
  }
}