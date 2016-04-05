#pragma once

#include "dllexport.h"

namespace aura {

  class Conductor;

  const float default_frequency = 440;

  typedef float (*Loop_Function)(float position);

  class MYTHIC_EXPORT Loop {
      double position = 0;
      float frequency;
      double increment;
      const int sample_rate;

  public:
      Loop(const int sample_rate, double frequency = default_frequency) :
        frequency(frequency),
        increment(frequency / sample_rate), sample_rate(sample_rate) { }

      Loop(Conductor &conductor, double frequency = default_frequency);

      float next();
      float next(int cycles);

      float get_frequency() const {
        return frequency;
      }

      void set_frequency(float value) {
        frequency = value;
        increment = frequency / sample_rate;
      }

      float get_position() const {
        return position;
      }
  };
}