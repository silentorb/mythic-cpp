#pragma once

#include "Frame_Info.h"

namespace framing {

  class MYTHIC_EXPORT Frame : public Frame_Info {
  protected:
      void set_dimensions(float width, float height) {
        dimensions = glm::ivec2(width, height);
      }

      void set_dpi(glm::vec2 value) {
        dpi = value;
      }

      void set_dpi(float x, float y) {
        dpi = glm::ivec2(x, y);
      }

  public:
      bool closing = false;
      virtual void update_events() = 0;
      virtual void flip_buffer() = 0;
      virtual void free() = 0;
      virtual void initialize_window() = 0;

      void set_fullscreen(bool fullscreen) {
        Frame::fullscreen = fullscreen;
      }
  };
}
