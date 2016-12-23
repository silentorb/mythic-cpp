#pragma once

#include <aura/engineering/Engineer.h>
#include <math/utility.h>
#include <cmath>
#include "aura/processing/Fixed_Delay.h"
#include "aura/processing/Filter_Base.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class High_Pass_Filter : public Second_Order_Filter<Signal_Type, High_Pass_Filter<Signal_Type>> {

    public:
        High_Pass_Filter(unsigned int sample_rate) :
          Second_Order_Filter<Signal_Type, High_Pass_Filter<Signal_Type>>(sample_rate) {}

        static void pre_calculate(Second_Order_Calculations<Signal_Type> &result, float frequency, float sample_rate, float Q) {
          Second_Order_Side<Signal_Type> common(frequency, sample_rate, Q);
          auto j = 0.5 + common.B + common.y;
          result.a0 = j / 2;
          result.a1 = -j;
          result.a2 = result.a0;
          result.b1 = -2 * common.y;
          result.b2 = 2 * common.B;
        }
    };
  }
}