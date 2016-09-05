#pragma once

#include "Draw_Method.h"

namespace modeling {

  class Renderable_Mesh {
  public:
      virtual void render(Draw_Method mode) = 0;
  };
}