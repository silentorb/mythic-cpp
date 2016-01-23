#pragma once

#include "dllexport.h"

namespace resourceful {

  class MYTHIC_EXPORT Resource {
  protected:
      int reference_count = 0;

  public:
      virtual void load() = 0;
      virtual void free() = 0;
  };
}