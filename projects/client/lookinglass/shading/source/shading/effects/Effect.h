#pragma once

#include "dllexport.h"
//#include "shading/Program.h"
#include "glm/glm.hpp"

namespace shading {
  class Program;

    class MYTHIC_EXPORT Effect {
    protected:
        Program *const program;
        void set_vec4(unsigned int index, const glm::vec4 &value);
        void activate();
        unsigned int get_location(const char* name);
        Effect(Program &program);

    public:

//        unsigned int const get_program_id() const {
//          return program->get_id();
//        }

    };
}
