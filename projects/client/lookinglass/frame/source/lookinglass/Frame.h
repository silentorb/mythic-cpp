#pragma once
#include "dllexport.h"

namespace lookinglass {
  class MYTHIC_EXPORT Frame {
  public:
      bool fullscreen;
      bool closing = false;
      virtual void update_events() = 0;
      virtual int get_width() = 0;
      virtual int get_height() = 0;
      virtual void flip_buffer() = 0;
//      virtual void create_gl_context();
  };
}
