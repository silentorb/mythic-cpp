#pragma once

#include "commoner/dllexport.h"
#include "Draw_Method.h"
#include "glm/glm.hpp"

namespace modeling {
  class Mesh_Data;
}
namespace perspective {
  class Viewport;
}
using namespace perspective;

namespace glow {
  class Capabilities;
}
namespace lookinglass {


  class MYTHIC_EXPORT Glass {
  private:
      const glow::Capabilities &capabilities;
      Viewport *viewport;

  public:
      Glass(Viewport &viewport);
//      void draw_mesh(modeling::Mesh_Data &mesh, Draw_Method draw_method);

      Viewport &get_viewport() const;

      void set_viewport(Viewport &viewport);

      const glm::ivec2 &get_viewport_dimensions() const;
			static Glass &get_instance();
  };

}

