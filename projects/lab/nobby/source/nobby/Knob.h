#pragma once

namespace nobby {

  template<typename T>
  class Knob {
      T value;
      const T min;
      const T max;

  public:
      Knob(T default_value, T min, T max) :
        value(default_value), min(min), max(max) {}

      T get_value() const {
        return value;
      }

      void set_value(T value) {
        this->value = value;
      }

      T get_min() const {
        return min;
      }

      T get_max() const {
        return max;
      }

      T get_normalized() const {
        return (value - min) / (max - min);
      }

      void set_normalized(float normalized_value){
        value = min + normalized_value * (max - min);
      }
  };
}