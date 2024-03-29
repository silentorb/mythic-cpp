#pragma once


#include "glm/vec2.hpp"

namespace framing {

  class Frame_Info {
  public:
      virtual const glm::ivec2 &get_dimensions() const = 0;
      virtual const glm::ivec2 &get_dpi() const = 0;
      virtual bool is_fullscreen() const = 0;
      virtual const glm::ivec2 get_inches() const = 0;
      virtual float get_pixel_scale() const = 0;
  };
}