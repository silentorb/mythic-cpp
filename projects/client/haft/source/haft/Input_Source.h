#pragma once

#include "dllexport.h"
#include "Input_State.h"

namespace haft {
  class MYTHIC_EXPORT Input_Source {
  public:
      virtual Input_State *get_input_state() = 0;
  };

}