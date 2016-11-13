#pragma once

#include <aura/engineering/Buffer.h>
#include "commoner/dllexport.h"
#include "Loop.h"
#include "Generator.h"

namespace aura {

  namespace engineering {
    class Engineer;
  }

  class Oscillator {
      Loop loop;
      Loop_Function operation;
      engineering::Engineer &engineer;
      Generator frequency_generator;

  public:
      Oscillator(engineering::Engineer &engineer, float frequency, Loop_Function operation);
      Oscillator(engineering::Engineer &engineer, const Generator frequency_generator, Loop_Function operation);

      float get_frequency() const {
        return loop.get_frequency();
      }

      void set_frequency(float frequency) {
        loop.set_frequency(frequency);
      }

      void set_frequency_generator(const Generator &frequency_generator) {
        Oscillator::frequency_generator = frequency_generator;
      }

      float operator()();
  };

  typedef std::function<Oscillator *(engineering::Engineer &, float, Loop_Function)> Oscillator_Generator;
}