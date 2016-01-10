#pragma once

#include "dllexport.h"
#include "Input_State.h"
#include "Input_Configuration.h"

namespace haft {
  class MYTHIC_EXPORT Input_Source {
  protected:
      Input_Configuration &config;

  public:
      Input_Source(Input_Configuration &config) :
        config(config) { }

      virtual Input_State *get_input_state() = 0;

  };

}