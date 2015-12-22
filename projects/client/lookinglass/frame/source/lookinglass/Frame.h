#pragma once

namespace lookinglass {
  class Frame {
  public:
      bool fullscreen;
      bool closing = false;
      virtual void update() = 0;
      virtual int get_width() = 0;
      virtual int get_height() = 0;
//      virtual void create_gl_context();
  };
}
