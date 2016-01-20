#pragma once

#include "dllexport.h"
#include "shading/effects/Effect.h"
#include "glm/glm.hpp"
#include "lookinglass/Draw_Method.h"

using namespace shading::effects;
using namespace shading;
using namespace lookinglass;
using namespace glm;

namespace scenery {
  class MYTHIC_EXPORT Spatial_Effect : protected Effect {
  private:
      Draw_Method draw_method;

  public:
      Spatial_Effect(Program & program);
      void activate(mat4 &transform);

      Draw_Method get_draw_method() { return draw_method; }

      void set_draw_method(Draw_Method value) { draw_method = value; }
  };
}
