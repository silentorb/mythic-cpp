#pragma once

#include "commoner/dllexport.h"

namespace glow {

  class MYTHIC_EXPORT Version {
  public:
      int major;
      int minor;
      bool ES = false;

      Version();
      Version(int major, int minor);
      bool at_least(int major, int minor);
  };
}
