#pragma once


#include "glm/glm.hpp"

namespace shading {

  class Program;

  class Effect {
  protected:
      Program *const program;

  public:
      Effect(Program &program);
      Effect(const Effect&) = delete;
      virtual ~Effect();
      virtual void activate();

      Program &get_program() const {
        return *program;
      }
  };
}
