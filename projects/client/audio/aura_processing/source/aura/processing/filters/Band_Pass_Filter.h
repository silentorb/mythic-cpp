#pragma once

#include <aura/engineering/Engineer.h>
#include <math/utility.h>
#include <cmath>
#include <aura/processing/Filter_Base.h>

namespace aura {
  namespace processing {

    template<typename Signal_Type>
    class Band_Pass_Filter : public Second_Order_Filter<Signal_Type, Band_Pass_Filter<Signal_Type>> {

    public:
        Band_Pass_Filter(unsigned int sample_rate, float Q) :
          Second_Order_Filter<Signal_Type, Band_Pass_Filter<Signal_Type>>(sample_rate, Q) {}

        static void pre_calculate(Second_Order_Calculations<Signal_Type> &result, float frequency, float sample_rate, float Q) {
          Second_Order_Side<Signal_Type> common(frequency, sample_rate, Q);
          auto j = 0.5 - common.B;
          result.a0 = j;
          result.a1 = 0;
          result.a2 = -j;
          result.b1 = -2 * common.y;
          result.b2 = 2 * common.B;
        }
    };
  }
}