#pragma once

#include <shading/Shader_Property.h>
#include "Effect.h"

namespace shading {

  class MYTHIC_EXPORT Color_Effect : public Effect {
  protected:
      Vector4_Property &color;

  public:
      Color_Effect(Program &program);

      void set_color(const glm::vec4 &value);
  };

}

