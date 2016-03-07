#pragma once

#include "dllexport.h"
#include <glm/vec4.hpp>
#include <bloom/layout/Bounds.h>

namespace drawing {
  class Draw;
}
using namespace glm;

namespace bloom {

  class MYTHIC_EXPORT Fill {
      vec4 color;

  public:
      void render(drawing::Draw &draw, const Bounds &bounds) const;

      void set_color(vec4 color) {
        this->color = color;
      }
  };
}