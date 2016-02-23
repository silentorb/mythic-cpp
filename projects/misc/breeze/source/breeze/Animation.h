#pragma once

#include "dllexport.h"


namespace breeze {

  class MYTHIC_EXPORT Animation : no_copy {
      float start;
      float duration;

  public:

      Animation(float start, float duration) : start(start), duration(duration) { }

      virtual void update(float delta) = 0;
  };
}