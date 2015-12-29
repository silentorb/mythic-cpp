#pragma once
#include "dllexport.h"

#include "Draw_Method.h"

namespace lookinglass {
  namespace glow {
    class MYTHIC_EXPORT Capabilities;
  }
  namespace modeling {
    class MYTHIC_EXPORT Mesh_Data;
  }
  class MYTHIC_EXPORT Glass {
  private:
      glow::Capabilities &capabilities;
  public:
      Glass(glow::Capabilities &capabilities);
      void draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method);
  };

}

