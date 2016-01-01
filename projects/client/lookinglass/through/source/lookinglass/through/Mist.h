#pragma once

#include "dllexport.h"

#include <map>
#include "lookinglass/shading/Program.h"
#include "Struct_Info.h"

using namespace std;

namespace lookinglass {
  using namespace shading;

    namespace through {

      template<typename T>
      class MYTHIC_EXPORT Mist : public Program_Add_Listener {
      public:
          virtual void initialize(Struct_Info* info) = 0;
          virtual void add_program(Program & program) = 0;
          virtual void update(T *data) = 0;
      };

      }
}