#pragma once

#include "Axis_Value.h"
#include "Measurement.h"

// Realized since calculated results are near to far, near and far cannot be properly generalized
// and these helper classes probably will not be used.
namespace bloom {

  class Far;

  class Near {
  public:

      inline static float get(const Axis_Value &value) {
        return value.near;
      }

      inline static const Measurement &get(const Axis_Measurement &value) {
        return value.near;
      }

      using other = Far;

  };

  class Far {
  public:

      inline static float get(const Axis_Value &value) {
        return value.far;
      }

      inline static const Measurement &get(const Axis_Measurement  &value) {
        return value.far;
      }

      using other = Near;
  };
}