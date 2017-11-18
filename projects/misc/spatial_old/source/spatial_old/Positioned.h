#pragma once

#include "glm/glm.hpp"

using namespace glm;

namespace spatial_old {

  class Positioned {
  public:
      virtual void set_position(const vec3 &value) = 0;
      virtual vec3 &get_position() = 0;
  };
}