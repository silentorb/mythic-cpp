#pragma once

#include "commoner/dllexport.h"
#include <shading/effects/Color_Effect.h>
#include <perspective/Viewport.h>

namespace typography {

  class MYTHIC_EXPORT Text_Effect : protected shading::Color_Effect {
      perspective::Viewport *viewport;

  public:
      Text_Effect(shading::Program &program, perspective::Viewport &viewport) :
        viewport(&viewport), Color_Effect(program) { }

      void activate(const vec4 &color, const mat4 &transform);

      perspective::Viewport &get_viewport() const {
        return *viewport;
      }
  };
}