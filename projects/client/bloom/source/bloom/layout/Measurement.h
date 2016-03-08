#pragma once

#include <glm/vec2.hpp>
#include "dllexport.h"

namespace bloom {

  enum class Measurements {
      units,
      stretch
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

      float get_value() const {
        return value;
      }

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

      glm::vec2 get_vec2() const {
        return glm::vec2(x.get_value(), y.get_value());
      }
  };

  struct MYTHIC_EXPORT Vector4 {
      Vector2 near;
      Vector2 far;

      Vector4() { }

      Vector4(const Vector2 &near, const Vector2 &far) : near(near), far(far) { }
  };
}