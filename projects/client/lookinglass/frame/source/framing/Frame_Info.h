#pragma once

#include "dllexport.h"
#include "glm/vec2.hpp"

namespace framing {

  class MYTHIC_EXPORT Frame_Info {
  protected:
      glm::ivec2 dimensions;
      glm::ivec2 dpi = glm::ivec2(0, 0);
      bool fullscreen;

  public:

      const glm::ivec2 &get_dimensions() const {
        return dimensions;
      }

      const glm::ivec2 &get_dpi() const {
        return dpi;
      }

      bool is_fullscreen() const {
        return fullscreen;
      }

  };
}