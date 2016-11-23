#pragma once

#include "commoner/dllexport.h"
#include <functional>

namespace aura {

  const float default_frequency = 440;

  typedef std::function<float(float position)> Loop_Function;

  class Loop {
      long double position = 0;
      long double increment;
      const unsigned int sample_rate;
//      long step = -1;

  public:
      Loop(const unsigned int sample_rate, double frequency = default_frequency) :
        increment(frequency / sample_rate), sample_rate(sample_rate) {
      }

      long double update();

      long double operator()() {
        return update();
      }

      long double update(bool &looped);

      float get_frequency() const {
        return (float) increment * sample_rate;
      }

      void set_frequency(float frequency) {
        increment = frequency / sample_rate;
      }

      long double get_next() const {
        return position;
      }

      void set_position(double value) {
        position = value;
      }
  };
}