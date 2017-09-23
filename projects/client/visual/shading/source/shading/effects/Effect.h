#pragma once

#include "commoner/dllexport.h"
#include "glm/glm.hpp"

namespace shading {

  class Program;

  class Effect : no_copy {
  protected:
      Program *const program;

  public:
      Effect(Program &program);
      virtual ~Effect();
      virtual void activate();

      Program &get_program() const {
        return *program;
      }
  };
}
