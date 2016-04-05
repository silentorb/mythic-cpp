#pragma once

#include "dllexport.h"

namespace aura {

  class Engineer;

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

      Loop(Engineer &conductor, double frequency = default_frequency);

      float next();
      float next(int cycles);

      float get_frequency() const {
        return frequency;
      }

      void set_frequency(float value) {
        frequency = value;
        increment = frequency / sample_rate;
      }

      double get_position() const {
        return position;
      }

      void set_position(double value) {
        position = value;
      }
  };
}