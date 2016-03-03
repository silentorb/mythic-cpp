#pragma once

#include "dllexport.h"
#include "glm/vec2.hpp"

namespace lookinglass {

  class MYTHIC_EXPORT Frame {
      glm::ivec2 dimensions;

  protected:
      void set_dimensions(float width, float height) {
        dimensions = glm::ivec2(width, height);
      }

  public:
      bool fullscreen;
      bool closing = false;
      virtual void update_events() = 0;
      virtual void flip_buffer() = 0;
      virtual void free() = 0;
      virtual void initialize_window() = 0;
//      virtual void create_gl_context();

      const glm::ivec2 &get_dimensions() const {
        return dimensions;
      }
  };
}
