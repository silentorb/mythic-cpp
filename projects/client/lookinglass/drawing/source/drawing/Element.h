#pragma once

#include "commoner/dllexport.h"

namespace drawing {

  class MYTHIC_EXPORT Element {
  public:
      virtual void render() = 0;
  };
}