#pragma once

#include <aura/engineer/Buffer.h>
#include "dllexport.h"
#include "Loop.h"
#include "Generator.h"

namespace aura {
  class Engineer;

  class MYTHIC_EXPORT Oscillator {
      Loop loop;
      Loop_Function operation;
      Engineer &engineer;
      Shared_Generator frequency_generator;

  public:
      Oscillator(Engineer &engineer, float frequency, Loop_Function operation);
      Oscillator(Engineer &engineer, const Shared_Generator &frequency_generator, Loop_Function operation);

      float get_frequency() const {
        return loop.get_frequency();
      }

      void set_frequency(float frequency) {
        loop.set_frequency(frequency);
      }

      void set_frequency_generator(const Shared_Generator &frequency_generator) {
        Oscillator::frequency_generator = frequency_generator;
      }

      float operator()();
  };

  typedef std::function<Oscillator *(Engineer &, float, Loop_Function)> Oscillator_Generator;
}