#pragma once
#include "dllexport.h"

#include "Glass.h"

namespace lookinglass {
  class MYTHIC_EXPORT Renderable {
  public:
      virtual void render(Glass &glass) = 0;

      virtual bool is_transparent() { return false; }
  };
}