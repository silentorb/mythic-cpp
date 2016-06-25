#pragma once
#include "dllexport.h"

namespace breeze {

  class MYTHIC_EXPORT Animation : no_copy {

  public:
      virtual ~Animation() { }

      virtual bool update(float delta) = 0;
  };
}