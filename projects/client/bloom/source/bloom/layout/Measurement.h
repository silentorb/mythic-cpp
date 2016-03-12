#pragma once

#include <glm/vec2.hpp>
#include "dllexport.h"

namespace bloom {

  enum class Measurements {
      units,
      stretch,
      percent,
      other_percent
  };

  const float UNIT_RESOLUTION = 1000;

  class MYTHIC_EXPORT Measurement {

      Measurements type;
      float value;

  public:

      Measurement() : type(Measurements::stretch), value(0) { }

      Measurement(Measurements type, float value) : type(type), value(value) { }

      Measurement(float value) : value(value), type(Measurements::units) { }

      Measurement(Measurements type) : type(type), value(0) { }

      Measurements get_type() const {
        return type;
      }

      void set_type(Measurements type) {
        Measurement::type = type;
      }

      float get_value(float parent_length) const {
        return type == Measurements::percent
               ? value * parent_length / 100
               : value;
      }

//      float get_value(Axis_Values &parent_values) const {
//        switch(type) {
//          case Measurements::percent:
//            return value * parent_length / 100;
//
//          case Measurements::other_percent:
//            return value * parent_length / 100;
//
//
//        }
//        return type == Measurements::percent
//               ? value * parent_length / 100
//               : value;
//      }

      float get_checked_value() const {
        return type == Measurements::units
               ? value
               : 0;
      }

      void set_value(float value) {
        Measurement::value = value;
      }
  };

  struct MYTHIC_EXPORT Vector2 {
      Measurement x;
      Measurement y;

      Vector2() { }

      Vector2(const Measurement &x, const Measurement &y) : x(x), y(y) { }

      glm::vec2 get_vec2(glm::vec2 parent_length) const {
        return glm::vec2(x.get_value(parent_length.x), y.get_value(parent_length.y));
      }
  };

  struct MYTHIC_EXPORT Vector4 {
      Vector2 near;
      Vector2 far;

      Vector4() { }

      Vector4(const Vector2 &near, const Vector2 &far) : near(near), far(far) { }
  };
}