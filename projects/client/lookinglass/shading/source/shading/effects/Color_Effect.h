#pragma once
#include "glm/glm.hpp"
#include "Effect.h"

using namespace glm;

namespace shading {
  class MYTHIC_EXPORT Color_Effect: public Effect {

  public:
      Color_Effect(Program &program) : Effect(program) { }

      void set_color(const vec4 &value);
  };

}

