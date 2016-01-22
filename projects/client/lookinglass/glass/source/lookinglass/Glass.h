#pragma once

#include "dllexport.h"
#include "Draw_Method.h"

namespace lookinglass {
  namespace perspective {
    class Viewport;
  }
  using namespace perspective;

  namespace glow {
    class MYTHIC_EXPORT Capabilities;
  }

  namespace modeling {
    class Mesh_Data;
  }

  class MYTHIC_EXPORT Glass {
  private:
      const glow::Capabilities &capabilities;
      Viewport *viewport;

  public:
      Glass(const glow::Capabilities &capabilities, Viewport &viewport);
      void draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method);

      Viewport &get_viewport() const;

      void set_viewport(Viewport &viewport);

      int get_viewport_width() const;
      int get_viewport_height() const;
  };

}

