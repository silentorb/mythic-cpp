#pragma once

#include "dllexport.h"

namespace glow {

  class MYTHIC_EXPORT Version {
  public:
      int major;
      int minor;
      bool ES = false;

      Version();
      Version(int major, int minor);
  };
}
