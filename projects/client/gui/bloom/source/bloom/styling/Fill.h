#pragma once

#include <glm/vec4.hpp>
#include <bloom/layout/Bounds.h>
#include "bloom/Draw_Interface.h"

namespace drawing {
  class Draw;
}
using namespace glm;

namespace bloom {

  class BLOOM_EXPORT Fill {
      vec4 color;

  public:
      void render(Draw_Interface &draw, const Bounds &bounds) const;

      void set_color(vec4 color) {
        this->color = color;
      }

      vec4 &get_color() {
        return color;
      }
  };
}