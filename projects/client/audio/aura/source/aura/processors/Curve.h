#pragma once

#include "dllexport.h"

namespace aura {
  enum Curve_Type {
      linear,
  };

  struct MYTHIC_EXPORT Curve {
      float x;
      float y;
      Curve_Type type;

      Curve(float x, float y, Curve_Type type) : x(x), y(y), type(type = Curve_Type::linear) { }
  };
}