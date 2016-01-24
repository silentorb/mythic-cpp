#pragma once

#include "dllexport.h"
#include <shading/effects/Color_Effect.h>

namespace typography {

  class MYTHIC_EXPORT Text_Effect : protected shading::Color_Effect {

  public:
      Text_Effect(shading::Program &program) : Color_Effect(program) { }

      void activate(const vec4 &color, const ivec2 &viewport_dimensions, const mat4 &transform);
  };
}