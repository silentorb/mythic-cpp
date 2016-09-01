#pragma once
#include "glm/glm.hpp"
#include "Effect.h"

using namespace glm;

namespace shading {

  class MYTHIC_EXPORT Color_Effect: protected Effect {

  public:
      Color_Effect(Program &program);

      void activate(const vec4 &value);
  };

}

