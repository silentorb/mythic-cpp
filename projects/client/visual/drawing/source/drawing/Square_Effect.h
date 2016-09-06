#pragma once

#include <shading/effects/Color_Effect.h>
#include <shading/Shader_Property.h>

namespace drawing {

  class Square_Effect : public shading::Color_Effect {
      shading::Matrix_Property &transform;

  public:
      Square_Effect(shading::Program &program);

      void set_transform(const glm::mat4 &value);
      virtual void activate() override;
  };
}