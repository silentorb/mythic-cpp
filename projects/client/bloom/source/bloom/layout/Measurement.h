#pragma once

#include <glm/vec2.hpp>
#include "dllexport.h"
#include <vector>
#include <stdexcept>
#include <memory>
#include "bloom/bloom_export.h"

using namespace std;

namespace bloom {

  enum class Measurements {
      pixel,
      stretch,
      shrink,
//      parent_aligned, // Deprecated
//      parent_perpendicular, // Deprecated
        percent,
      percent_perpendicular,
      vertical_units,
      units, // Deprecated
      horizontal_units,
//      complex
  };

  const float UNIT_RESOLUTION = 1000;

  class Measurement_Converter;

  class BLOOM_EXPORT Measurement {
      Measurements type;
      float value;

  protected:

//      float debug_value = -1;
//      unsigned long debug_index;
//      Measurement(Measurements type);

  public:

      Measurement() { }

      Measurements get_type() const {
        return type;
      }

//      virtual Measurement *clone() const {
//        return new Measurement(type, value);
//      };

//      Measurement(const Measurement &m) : Measurement(m.get_type()) { }

      Measurement(const Measurements type, float value) : type(type), value(value) { }

      Measurement(float value) : value(value), type(Measurements::pixel) { }

      template<typename Axis>
      float resolve(const glm::vec2 &parent_dimensions,
                    const Measurement_Converter &converter) const;

      float get_value() const {
        return value;
      }

      static float pixel_scale;
  };

//  class BLOOM_EXPORT Stretch_Measurement : public Measurement {
//  protected:
//      virtual Measurement *clone() const override {
//        return new Stretch_Measurement();
//      }
//
//  public:
//
//      Stretch_Measurement() : Measurement(Measurements::stretch) { }
//  };

//  class BLOOM_EXPORT Measurement : public Measurement {
//
//  protected:
//      virtual Measurement *clone() const override {
//        return new Measurement(get_type(), value);
//      }
//
//  public:
//
//      Measurement() : Measurement(Measurements::stretch), value(0) { }
//
//      Measurement(Measurements type, float value) : Measurement(type), value(value) {
//        debug_value = value;
//      }
//
//      Measurement(float value) : value(value), Measurement(Measurements::units) {
//        debug_value = value;
//      }
//
////      Measurement(Measurements type) : Measurement(type), value(0) { }
//
//      float get_value() const {
//        return value;
//      }
//  };

//  class BLOOM_EXPORT Complex_Measurement : public Measurement {
//      vector<shared_ptr<Measurement>> measurements;
//
//  protected:
//      virtual Measurement *clone() const override {
//        return new Complex_Measurement(measurements);
//      }
//
//  public:
//      Complex_Measurement(initializer_list<Measurement *> items) :
//        Measurement(Measurements::complex) {
//        for (auto &measurement:items) {
//          measurements.push_back(shared_ptr<Measurement>(measurement));
//        }
//      }
//
//      Complex_Measurement(const vector<shared_ptr<Measurement>> &measurements) :
//        measurements(measurements), Measurement(Measurements::complex) {
//
//      }
//
////      Complex_Measurement(const Complex_Measurement &m) : Complex_Measurement(m.measurements) { }
//
////      Complex_Measurement &operator=(Complex_Measurement const &m) {
////        measurements.empty();
////        for (auto &measurement:m.measurements) {
////          measurements.push_back(shared_ptr<Measurement>(measurement->clone()));
////        }
////      }
//
//      const vector<shared_ptr<Measurement>> &get_measurements() const {
//        return measurements;
//      }
//  };

  class BLOOM_EXPORT Vector2 {
      Measurement x;
      Measurement y;

  public:
      Vector2() : x(Measurement(Measurements::stretch, 0)),
                  y(Measurement(Measurements::stretch, 0)) { }

      Vector2(const Measurement &x, const Measurement &y) : x(x), y(y) { }

      Vector2(const Vector2 &v) : Vector2(v.x, v.y) { }

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
        x = value;
      }

      void set_y(const Measurement &value) {
        y = value;
      }

      void set_y(int value) {
        y = Measurement(value);
      }

      const Measurement &get_x() const {
        return x;
      }

      const Measurement &get_y() const {
        return y;
      }

//      const Measurement &get_x_pointer() const {
//        return x;
//      }
//
//      const Measurement &get_y_pointer() const {
//        return y;
//      }

      void set_values(Measurement &measurement) {
        set_x(measurement);
        set_y(measurement);
      }
  };

  struct BLOOM_EXPORT Vector4 {
      Vector2 near;
      Vector2 far;

      Vector4() { }

      Vector4(const Vector2 &near, const Vector2 &far) : near(near), far(far) { }

      void set_values(Measurement &measurement) {
        near.set_values(measurement);
        far.set_values(measurement);
      }

      void set_x_values(Measurement &measurement) {
        near.set_x(measurement);
        far.set_x(measurement);
      }

      void set_y_values(Measurement &measurement) {
        near.set_y(measurement);
        far.set_y(measurement);
      }
  };

  struct Axis_Measurement {
      Measurement near;
      Measurement length;
      Measurement far;
  };

  struct Axis_Measurements {
      Axis_Measurement x;
      Axis_Measurement y;
  };
}
