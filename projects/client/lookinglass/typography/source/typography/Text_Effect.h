#pragma once

#include "dllexport.h"
#include <shading/effects/Color_Effect.h>

namespace typography {

  class MYTHIC_EXPORT Text_Effect : protected shading::Color_Effect {
      ivec2 viewport_dimensions;

  public:
      Text_Effect(shading::Program &program, const ivec2 &viewport_dimensions) :
        viewport_dimensions(viewport_dimensions), Color_Effect(program) { }

      void activate(const vec4 &color, const mat4 &transform);

      void set_viewport_dimensions(const ivec2 &value) {
        viewport_dimensions = value;
      }

      const ivec2 &get_viewport_dimensions() const {
        return viewport_dimensions;
      }
  };
}