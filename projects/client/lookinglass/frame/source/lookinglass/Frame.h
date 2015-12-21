#pragma once

namespace lookinglass {
  class Frame {
  public:
      void *gl_context;

      int width;
      int height;
      bool fullscreen;
      bool closing = false;
      virtual void update() = 0;
  };
}
