#pragma once

#include "glm/glm.hpp"

using namespace glm;

namespace spatial {

  class Positioned {
  public:
      virtual void set_position(const vec3 &value) = 0;
      virtual const vec3 &get_position() const = 0;
  };
}