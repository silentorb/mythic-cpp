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

      virtual ~Knob() {

      }

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

      void set_normalized(float normalized_value) {
        value = min + normalized_value * (max - min);
      }

      virtual operator float() {
        return get_value();
      }
  };

  template<typename T, typename Data_Type>
  class Data_Knob : public Knob<T> {
      Data_Type data;

  public:
      Data_Knob(T default_value, T min, T max, Data_Type data) :
        Knob<T>(default_value, min, max), data(data) {}

      virtual ~Data_Knob() {

      }

      const Data_Type &get_data() const {
        return data;
      }
  };
}