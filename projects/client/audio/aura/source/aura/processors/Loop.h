#pragma once

#include "commoner/dllexport.h"
#include <functional>

namespace aura {

  namespace engineering {
    class Engineer;
  }

  const float default_frequency = 440;

  typedef std::function<float(float position)> Loop_Function;

  class MYTHIC_EXPORT Loop {
      double position = 0;
//      float frequency;
      double increment;
      const int sample_rate;

  public:
      Loop(const int sample_rate, double frequency = default_frequency) :
//        frequency(frequency),
        increment(frequency / sample_rate), sample_rate(sample_rate) { }

      Loop(engineering::Engineer &conductor, double frequency = default_frequency);

      float next();
//      float next(int cycles);
      float next(bool & looped);

      float get_frequency() const {
        return (float)increment * sample_rate;
      }

      void set_frequency(float frequency) {
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