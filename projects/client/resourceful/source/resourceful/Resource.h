#pragma once

#include "dllexport.h"

namespace resourceful {

  class MYTHIC_EXPORT Resource {
  protected:
      int reference_count = 0;

  public:
      virtual ~Resource() { }

      virtual void load() = 0;
      virtual void release() = 0;
  };
}