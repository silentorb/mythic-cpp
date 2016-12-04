#pragma once

#include "commoner/dllexport.h"

namespace aura {
  enum Curve_Type {
      linear,
  };

  struct Curve {
      float x;
      float y;
      Curve_Type type;

      Curve(float x, float y, Curve_Type type) : x(x), y(y), type(type = Curve_Type::linear) { }
  };
}