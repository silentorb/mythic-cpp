#pragma once

#include <aura/engineering/Engineer.h>
#include <math/utility.h>
#include <cmath>
#include "Fixed_Delay_Buffer.h"
#include "Filter_Base.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class High_Pass_Filter : public Second_Order_Filter<Signal_Type, High_Pass_Filter<Signal_Type>> {

    public:
        High_Pass_Filter(unsigned int sample_rate) :
          Second_Order_Filter<Signal_Type, High_Pass_Filter<Signal_Type>>(sample_rate) {}

        static void pre_calculate(Second_Order_Pre_Calculation &result, float frequency, float sample_rate, float Q) {
          auto arc = 2 * Pi * frequency / sample_rate;
          auto d = 1 / Q;
          auto k = d / 2 * sin(arc);
          auto B = 0.5 * (1 - k) / (1 + k);
          auto y = (0.5 + B) * cos(arc);
          auto j = 0.5 + B + y;
          result.a0 = j / 2;
          result.a1 = -j;
          result.a2 = result.a0;
          result.b1 = -2 * y;
          result.b2 = 2 * B;
        }
    };
  }
}