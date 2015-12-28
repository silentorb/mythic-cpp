#pragma once

#include "Draw_Method.h"

namespace lookinglass {
  namespace glow {
    class Capabilities;
  }
  namespace modeling {
    class Mesh_Data;
  }
  class Glass {
  private:
      glow::Capabilities &capabilities;
  public:
      Glass(glow::Capabilities &capabilities);
      void draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method);
  };

}

