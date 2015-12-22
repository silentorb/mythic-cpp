#pragma once

namespace lookinglass {
  class Frame {
  public:
      bool fullscreen;
      bool closing = false;
      virtual void update() = 0;
      virtual int get_width() = 0;
      virtual int get_height() = 0;
      virtual void flip_buffer() = 0;
      virtual void set_clear_color(float red, float green, float blue, float alpha) = 0;
      virtual void clear() = 0;
//      virtual void create_gl_context();
  };
}
