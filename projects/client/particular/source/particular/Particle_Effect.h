#pragma once

#include <shading/Shader_Property.h>
#include "shading/Program.h"
#include "glm/mat4x4.hpp"
#include "commoner/dllexport.h"

using namespace shading;

namespace scenery {

  class MYTHIC_EXPORT Particle_Effect : public Program {
      Matrix_Property model_property;

  public:
      Particle_Effect(const string &name, const string &first, const string &second,
                      Vertex_Schema &vertex_schema) :
        Program(name, first, second, vertex_schema),
        model_property("model", this) { }

      virtual void activate() override;

  };
}