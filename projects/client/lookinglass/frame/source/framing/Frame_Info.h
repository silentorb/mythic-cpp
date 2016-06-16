#pragma once

#include "dllexport.h"
#include "glm/vec2.hpp"

namespace framing {

  class MYTHIC_EXPORT Frame_Info {
  public:
      virtual const glm::ivec2 &get_dimensions() const = 0;
      virtual const glm::ivec2 &get_dpi() const = 0;
      virtual bool is_fullscreen() const = 0;
      virtual const glm::ivec2 get_inches() const = 0;
  };
}