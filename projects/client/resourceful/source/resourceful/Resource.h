#pragma once

#include "dllexport.h"

namespace resourceful {

  class MYTHIC_EXPORT Resource {
  protected:
      int reference_count = 0;

  public:
//      ~Resource();
      virtual void free() = 0;
      virtual void load() = 0;
  };
}