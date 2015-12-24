#pragma once

#include "Glass.h"

namespace lookinglass {
  class Renderable {
  public:
      virtual void render(Glass &glass) = 0;

      virtual bool is_transparent() { return false; }
  };
}