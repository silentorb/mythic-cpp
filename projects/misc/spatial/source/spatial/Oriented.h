#pragma once

#include "glm/glm.hpp"

using namespace glm;

namespace spatial {

  class Oriented {
  public:
      virtual void set_orientation(const quat &value) = 0;
      virtual const quat &get_orientation() const = 0;
  };
}