#pragma once


#include "Input_State.h"
#include "Input_Configuration.h"

namespace haft {
  class Input_Source {
  protected:
      Input_Configuration &config;

  public:
      Input_Source(Input_Configuration &config) :
        config(config) { }

      virtual Input_State *get_input_state() = 0;

  };

}