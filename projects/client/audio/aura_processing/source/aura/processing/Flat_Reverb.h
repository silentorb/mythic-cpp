#pragma once

#include <cstdlib>
#include "Fixed_Delay.h"
#include "utility.h"
#include "aura/primitives/Decibels.h"
#include "aura/primitives/Signal.h"

namespace aura {
  namespace processing {

    template<typename Signal_Type, size_t Size>
    class Flat_Reverb {
        Fixed_Delay<Signal_Type, Size> delay;
        Decibels decay = 0.5;

    public:
        Flat_Reverb() {

        }

        Signal_Type operator()(const Signal_Type &value) {
          float mixed = value + delay.get_last();
          delay(mixed * decay);
          return mixed;
        }

        void set_decay(const Decibels &value) {
          decay = value;
        }
    };
  }
}