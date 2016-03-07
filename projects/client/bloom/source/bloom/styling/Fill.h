#pragma once

#include "dllexport.h"
#include <glm/vec4.hpp>
#include <bloom/layout/Bounds.h>
#include <drawing/Draw.h>

using namespace glm;

namespace bloom {

  class MYTHIC_EXPORT Fill {
      vec4 color;

  public:
      void render(drawing::Draw &draw, const Bounds &bounds) const{
        draw.draw_square(bounds.get_position().x, bounds.get_position().y, bounds.get_dimensions().x,
                         bounds.get_dimensions().y, color, true);
      }

      void set_color(vec4 color) {
        this->color = color;
      }
  };
}