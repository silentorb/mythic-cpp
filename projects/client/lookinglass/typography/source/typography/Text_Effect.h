#pragma once

#include "dllexport.h"
#include <shading/effects/Color_Effect.h>
#include <lookinglass/perspective/Viewport.h>

namespace typography {

  class MYTHIC_EXPORT Text_Effect : protected shading::Color_Effect {
      lookinglass::perspective::Viewport *viewport;

  public:
      Text_Effect(shading::Program &program, lookinglass::perspective::Viewport &viewport) :
        viewport(&viewport), Color_Effect(program) { }

      void activate(const vec4 &color, const mat4 &transform);

      lookinglass::perspective::Viewport &get_viewport() const {
        return *viewport;
      }
  };
}