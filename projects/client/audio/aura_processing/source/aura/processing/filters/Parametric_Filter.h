#pragma once

#include <aura/processing/Filter_Base.h>
#include <math/utility.h>
#include <cmath>
#include <aura/processing/utility.h>

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Parametric_Filter : public Resonant_Filter_Base<Signal_Type> {
        Fixed_Delay_Buffer<Signal_Type, 2> original_buffer;
        Fixed_Delay_Buffer<Signal_Type, 2> output_buffer;
        Second_Order_Mix_Calculations calculation;
        float gain;

        Signal_Type pre_calculate() {
          auto arc = 2 * Pi * frequency / sample_rate;
          auto m = dB(gain);
          auto L = 4 / (1 + m);
          auto k = L * tan(arc / 2 * Q);
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
        Parametric_Filter(unsigned int sample_rate) :
          Resonant_Filter_Base<Signal_Type>(sample_rate) {}

        Signal_Type operator()(Signal_Type input) {
          if (this->changed) {
//            Calculation_Type::pre_calculate(calculation, this->frequency, this->sample_rate, this->Q);
            this->changed = false;
          }

          auto output = calculation.process_mixed(input, original_buffer, output_buffer);
          original_buffer.update(input);
          output_buffer.update(output);
          return output;
        }

    };
  }
}