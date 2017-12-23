#pragma once

#include <shading/Shader_Property.h>
#include "shading/Program.h"
#include "glm/mat4x4.hpp"

#include <shading/effects/Effect.h>

using namespace shading;

namespace scenery {

  class Particle_Effect : public Effect {
      Matrix_Property &model_property;

  public:
      Particle_Effect(Program &program) :
        Effect(program),
        model_property(program.create_property<shading::Matrix_Property>("model")) {}

      virtual void activate();

  };
}