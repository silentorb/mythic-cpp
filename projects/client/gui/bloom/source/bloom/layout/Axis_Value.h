#pragma once
#include <glm/vec2.hpp>

namespace bloom {

  struct Axis_Value {
      float near, far;

      Axis_Value operator+(float value) {
        return {near + value, far + value};
      }
  };

  struct Axis_Values {
      glm::vec2 position;
      glm::vec2 dimensions;
  };

}