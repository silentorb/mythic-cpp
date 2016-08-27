#pragma once

#include "commoner/dllexport.h"
#include "glm/glm.hpp"

namespace shading {

  class Program;


  class MYTHIC_EXPORT Effect : no_copy {
  protected:
      Program *const program;
      void set_vec4(unsigned int index, const glm::vec4 &value);
      virtual void activate();
      int get_location(const char *name);
      Effect(Program &program);

  public:
      virtual ~Effect();

      Program &get_program() const {
        return *program;
      }
  };
}
