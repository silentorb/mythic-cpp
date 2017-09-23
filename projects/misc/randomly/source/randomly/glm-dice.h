#pragma once
#include "glm/vec3.hpp"
#include "Dice.h"

using namespace glm;

namespace randomly {

  vec3 get_vec3(Dice& dice,const vec3 min, const vec3 max) {
    return vec3(
      dice.get_float_relative(min.x, max.x),
      dice.get_float_relative(min.y, max.y),
      dice.get_float_relative(min.z, max.z)
    );
  }
}