#pragma once

#include "Fixed_Delay_Buffer.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Filter_Base {
    protected:
        const unsigned int sample_rate;
        bool changed = true;
        float frequency;

    public:
        Filter_Base(const unsigned int sample_rate) : sample_rate(sample_rate) {}

        void set_frequency(float value) {
          if (frequency == value)
            return;

          frequency = value;
          changed = true;
        }

    };

    template<typename Signal_Type>
    class Resonant_Filter_Base : public Filter_Base<Signal_Type> {
    protected:
        float Q;

    public:
        Resonant_Filter_Base(unsigned int sample_rate) : Filter_Base<Signal_Type>(sample_rate) {}

        void set_Q(float value) {
          if (Q == value)
            return;

          Q = value;
          this->changed = true;
        }
    };

    struct Second_Order_Pre_Calculation {
        float a0, a1, a2, b1, b2;
    };

    template<typename Signal_Type, typename Calculation_Type>
    class Second_Order_Filter : public Resonant_Filter_Base<Signal_Type> {
        Fixed_Delay_Buffer<float, 2> original_buffer;
        Fixed_Delay_Buffer<float, 2> output_buffer;
        Second_Order_Pre_Calculation calculation;

    public:
        Second_Order_Filter(unsigned int sample_rate) :
          Resonant_Filter_Base<Signal_Type>(sample_rate) {}

        float operator()(float input) {
          if (this->changed) {
            Calculation_Type::pre_calculate(calculation, this->frequency, this->sample_rate, this->Q);
            this->changed = false;
          }

          auto output = calculation.a0 * input
                        + calculation.a1 * original_buffer[0]
                        + calculation.a2 * original_buffer[1]
                        - calculation.b1 * output_buffer[0]
                        - calculation.b2 * output_buffer[1];
          original_buffer.update(input);
          output_buffer.update(output);
          return output;
        }

    };
  }
}