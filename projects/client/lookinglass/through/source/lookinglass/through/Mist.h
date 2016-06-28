#pragma once

#include "dllexport.h"

#include <map>
#include "shading/Program.h"
#include "Struct_Info.h"

using namespace std;
using namespace shading;

namespace lookinglass {

  namespace through {

    template<typename T>
    class MYTHIC_EXPORT Mist : public Program_Add_Listener {
    public:
        virtual ~Mist() { }

        virtual void initialize(Struct_Info *info) = 0;
        virtual void add_program(Program &program) = 0;
        virtual void remove_program(Program &program) = 0;
        virtual void update(T *data) = 0;
        virtual void release() = 0;
    };

  }
}