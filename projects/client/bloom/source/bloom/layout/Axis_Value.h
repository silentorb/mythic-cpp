#pragma once

namespace bloom {

  struct Axis_Value {
      float near, far;

      Axis_Value operator+(float value) {
        return {near + value, far + value};
      }
  };

  struct Axis_Values {
      Axis_Value x;
      Axis_Value y;
  };

}