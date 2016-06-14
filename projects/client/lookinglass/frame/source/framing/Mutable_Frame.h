#pragma once

#include "Frame_Info.h"

namespace framing {

  class MYTHIC_EXPORT Mutable_Frame : public Frame_Info {
      glm::ivec2 pixels;
      glm::ivec2 dpi = glm::ivec2(0, 0);
      bool fullscreen;

  public:

      void set_fullscreen(bool fullscreen) {
        Mutable_Frame::fullscreen = fullscreen;
      }

      virtual const glm::ivec2 &get_dimensions() const override {
        return pixels;
      }

      virtual const glm::ivec2 &get_dpi() const override {
        return dpi;
      }

      virtual bool is_fullscreen() const override {
        return fullscreen;
      }

      virtual const glm::ivec2 get_inches() const override {
        return dpi / pixels;
      }

      void set_dimensions(float width, float height) {
        pixels = glm::ivec2(width, height);
      }

      void set_dpi(glm::vec2 value) {
        dpi = value;
      }

      void set_dpi(float x, float y) {
        dpi = glm::ivec2(x, y);
      }

  };
}
