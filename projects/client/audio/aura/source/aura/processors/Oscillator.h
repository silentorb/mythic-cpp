#pragma once

#include <aura/engineer/Buffer.h>
#include "dllexport.h"
#include "Loop.h"

namespace aura {
  class Engineer;

  class MYTHIC_EXPORT Oscillator {
      Loop loop;
      Loop_Function operation;
      Engineer & engineer;

  public:
      Oscillator(Engineer &engineer, float frequency, Loop_Function operation);

//      void update(Buffer & buffer);
      float update();

      float get_frequency() const {
        return loop.get_frequency();
      }

      void set_frequency(float frequency) {
        loop.set_frequency(frequency);
      }
  };
}