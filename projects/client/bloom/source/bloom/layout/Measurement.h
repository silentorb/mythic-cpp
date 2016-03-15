#pragma once

#include <glm/vec2.hpp>
#include "dllexport.h"
#include <vector>
#include <stdexcept>
#include <memory>

using namespace std;

namespace bloom {

  enum class Measurements {
      units,
      stretch,
      parent_aligned,
      parent_perpendicular,
      vertical_units,
      horizontal_units,
      complex
  };

  const float UNIT_RESOLUTION = 1000;

  class Measurement_Converter;

  class MYTHIC_EXPORT Measurement {

      const Measurements type;

  protected:
      Measurement(Measurements type);

      float debug_value = -1;
      unsigned long debug_index;

  public:

      Measurements get_type() const {
        return type;
      }

      virtual Measurement *clone() const = 0;

//      Measurement(const Measurement &m) : Measurement(m.get_type()) { }

      template<typename Axis>
      float resolve(const glm::vec2 &parent_dimensions,
                    const Measurement_Converter &converter) const;
  };

  class MYTHIC_EXPORT Stretch_Measurement : public Measurement {
  protected:
      virtual Measurement *clone() const override {
        return new Stretch_Measurement();
      }

  public:

      Stretch_Measurement() : Measurement(Measurements::stretch) { }
  };

  class MYTHIC_EXPORT Simple_Measurement : public Measurement {
      float value;

  protected:
      virtual Measurement *clone() const override {
        return new Simple_Measurement(get_type(), value);
      }

  public:

      Simple_Measurement() : Measurement(Measurements::stretch), value(0) { }

      Simple_Measurement(Measurements type, float value) : Measurement(type), value(value) {
        int k = 0;
        debug_value = value;
      }

      Simple_Measurement(float value) : value(value), Measurement(Measurements::units) {
        int k = 0;
        debug_value = value;
      }

//      Simple_Measurement(Measurements type) : Measurement(type), value(0) { }

      float get_value() const {
        return value;
      }
  };

  class MYTHIC_EXPORT Complex_Measurement : public Measurement {
      vector<shared_ptr<Measurement>> measurements;

  protected:
      virtual Measurement *clone() const override {
        return new Complex_Measurement(measurements);
      }

  public:
      Complex_Measurement(initializer_list<Measurement *> items) :
        Measurement(Measurements::complex) {
        for (auto &measurement:items) {
          measurements.push_back(shared_ptr<Measurement>(measurement));
        }
      }

      Complex_Measurement(const vector<shared_ptr<Measurement>> &measurements) :
        measurements(measurements), Measurement(Measurements::complex) {

      }

//      Complex_Measurement(const Complex_Measurement &m) : Complex_Measurement(m.measurements) { }

//      Complex_Measurement &operator=(Complex_Measurement const &m) {
//        measurements.empty();
//        for (auto &measurement:m.measurements) {
//          measurements.push_back(shared_ptr<Measurement>(measurement->clone()));
//        }
//      }

      const vector<shared_ptr<Measurement>> &get_measurements() const {
        return measurements;
      }
  };

  class MYTHIC_EXPORT Vector2 {
      shared_ptr<Measurement> x;
      shared_ptr<Measurement> y;

  public:
      Vector2() : x(static_cast<Measurement *>(new Stretch_Measurement())),
                  y(static_cast<Measurement *>(new Stretch_Measurement())) { }

      Vector2(const Measurement &x, const Measurement &y) : x(x.clone()), y(y.clone()) { }

      Vector2(const Vector2 &v) : Vector2(*v.x, *v.y) { }

//      Vector2 &operator=(const Vector2 &other) {
////        set_x(*v.x);
////        set_y(*v.y);
//        x = other.x;
//        y = other.y;
//        return *this;
//      }

      glm::vec2 get_vec2(const glm::vec2 &parent_dimensions,
                         const Measurement_Converter &converter) const;

      void set_x(const Measurement &value) {
        x = shared_ptr<Measurement>(value.clone());
      }

      void set_y(const Measurement &value) {
        y = shared_ptr<Measurement>(value.clone());
      }

      const Measurement &get_x() const {
        return *x;
      }

      const Measurement &get_y() const {
        return *y;
      }

      const shared_ptr<Measurement> &get_x_pointer() const {
        return x;
      }

      const shared_ptr<Measurement> &get_y_pointer() const {
        return y;
      }
  };

  struct MYTHIC_EXPORT Vector4 {
      Vector2 near;
      Vector2 far;

      Vector4() { }

      Vector4(const Vector2 &near, const Vector2 &far) : near(near), far(far) { }
  };
}