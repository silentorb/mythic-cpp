#pragma once

#include "dllexport.h"

namespace framing {

  class MYTHIC_EXPORT Device_Frame {
  public:
      virtual void update_events() = 0;
      virtual void flip_buffer() = 0;
      virtual void free() = 0;
      virtual void initialize_window() = 0;
      virtual bool is_closing() = 0;
  };
}
