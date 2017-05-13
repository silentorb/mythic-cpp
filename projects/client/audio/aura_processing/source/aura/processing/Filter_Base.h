#pragma once

#include "Fixed_Delay.h"
#include <math/utility.h>
#include <cmath>

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
        Resonant_Filter_Base(unsigned int sample_rate, float Q) :
          Filter_Base<Signal_Type>(sample_rate), Q(Q) {}

        void set_Q(float value) {
          if (Q == value)
            return;

          Q = value;
          this->changed = true;
        }
    };

    template<typename Signal_Type>
    struct Second_Order_Calculations {
        Signal_Type a0, a1, a2, b1, b2;

        Signal_Type process(Signal_Type input, Fixed_Delay<Signal_Type, 2> original_buffer,
                            Fixed_Delay<Signal_Type, 2> output_buffer) const {
          return 0
                 + a0 * input
                 + a1 * original_buffer[0]
                 + a2 * original_buffer[1]
                 - b1 * output_buffer[0]
                 - b2 * output_buffer[1];
        }
    };

    template<typename Signal_Type>
    struct Second_Order_Mix_Calculations : public Second_Order_Calculations<Signal_Type> {
        Signal_Type c, d;

//        Signal_Type process_mixed(Signal_Type input, Fixed_Delay<Signal_Type, 2> original_buffer,
//                                  Fixed_Delay<Signal_Type, 2> output_buffer) const {
//          auto processed = Second_Order_Calculations<Signal_Type>::process(input, original_buffer, output_buffer);
//          return
//            c * processed
//            + d * input;
//        }
    };

    template<typename Signal_Type, typename Calculation_Type>
    class Second_Order_Filter : public Resonant_Filter_Base<Signal_Type> {
        Fixed_Delay<Signal_Type, 2> original_buffer;
        Fixed_Delay<Signal_Type, 2> output_buffer;
        Second_Order_Calculations<Signal_Type> calculation;

    public:
        Second_Order_Filter(unsigned int sample_rate, float Q) :
          Resonant_Filter_Base<Signal_Type>(sample_rate, Q) {}

        Signal_Type operator()(Signal_Type input) {
          if (this->changed) {
            Calculation_Type::pre_calculate(calculation, this->frequency, this->sample_rate, this->Q);
            this->changed = false;
          }

          auto output = calculation.process(input, original_buffer, output_buffer);
          original_buffer.update(input);
          output_buffer.update(output);
          return output;
        }

    };
  }

  template<typename Signal_Type>
  struct Second_Order_Side {
      Signal_Type B, y;

      Second_Order_Side(float frequency, float sample_rate, float Q) {
//        auto arc = 2 * Pi * frequency / sample_rate;
          auto arc = frequency / sample_rate;
        auto d = 1 / Q;
//        auto k = d / 2 * sin(arc);
          auto k = generate::sine(arc);
        B = 0.5 * (1 - k) / (1 + k);
//        y = (0.5 + B) * cos(arc);
          auto cos_arg = arc + 0.5f;
          if (cos_arg > 1)
              cos_arg -= 1;
          
          y = (0.5 + B) * generate::sine(cos_arg);
      }
  };

  template<typename Signal_Type>
  struct Second_Order_Middle {
      Signal_Type B, y;

      Second_Order_Middle(float frequency, float sample_rate, float Q) {
        auto arc = 2 * Pi * frequency / sample_rate;
          auto arc2 = frequency / sample_rate;
        auto k = tan(arc / (2 * Q));
        B = 0.5 * (1 - k) / (1 + k);
//          y = (0.5 + B) * generate::sine(arc + 0.5f);
//                  y = (0.5 + B) * cos(arc);
          auto cos_arg = arc2 + 0.5f;
          if (cos_arg > 1)
              cos_arg -= 1;
          
          y = (0.5 + B) * generate::sine(cos_arg);
      }
  };
}