#pragma once

#include <cstdlib>
#include <aura/processing/filters/Low_Pass_Filter.h>
#include "Fixed_Delay_Buffer.h"
#include "utility.h"
#include "Decibels.h"
#include "Signal.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type, size_t Size>
    class Low_Pass_Reverb {
        Fixed_Delay_Buffer<Signal_Type, Size> delay;
        Decibels decay = 0.5;
        Low_Pass_Filter<Signal_Type> filter;

    public:
        Low_Pass_Reverb(unsigned int sample_rate) :
          filter(sample_rate) {

        }

        Signal_Type operator()(const Signal_Type &value) {
          float mixed = value + delay.get_last();
          delay(filter(mixed * decay));
          return mixed;
        }

        void set_decay(const Decibels &value) {
          decay = value;
        }

        Low_Pass_Filter<Signal_Type> &get_filter() {
          return filter;
        }
    };
  }
}