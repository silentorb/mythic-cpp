#pragma once

#include "dllexport.h"

namespace drawing {

  class MYTHIC_EXPORT Element {
  public:
      virtual void render() = 0;
  };
}