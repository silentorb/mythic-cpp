#pragma once

#include "dllexport.h"
#include "shading/Program.h"

namespace shading {
//  class Program;

    class MYTHIC_EXPORT Effect {
    protected:
        Program *const program;

    public:
        Effect(Program &program);
        void activate();


        unsigned int const get_program_id() const {
          return program->get_id();
        }
    };
}
