#pragma once

#include "dllexport.h"

namespace bloom {

  enum Measurements {
      units,
      stretch
  };

  class MYTHIC_EXPORT Measurement {

      Measurements type;
      float value;

  public:

      Measurement() : type(Measurements::units), value(0) { }

      Measurement(Measurements type, float value) : type(type), value(value) { }

      Measurement(float value) : value(value), type(Measurements::units) { }

      Measurement(Measurements type) : type(type), value(0) { }
  };
}