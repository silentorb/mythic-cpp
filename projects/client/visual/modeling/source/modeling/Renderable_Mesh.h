#pragma once

#include "Draw_Method.h"

namespace modeling {

  class Renderable_Mesh {
  public:
      virtual void render(Draw_Method mode) = 0;
  };

  class Renderable_Mesh_With_Opacity : public virtual Renderable_Mesh {
  public:
      virtual bool has_opacity() const = 0;
  };
}