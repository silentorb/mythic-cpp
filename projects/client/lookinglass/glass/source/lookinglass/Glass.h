#pragma once

#include "Draw_Method.h"
#include "Mesh_Data.h"

namespace lookinglass {
  namespace glow {
    class Capabilities;
  }
  class Glass {
  private:
      glow::Capabilities &capabilities;
  public:
      Glass(glow::Capabilities &capabilities);
      void draw_mesh(Mesh_Data &mesh, Draw_Method draw_method);
  };

}

