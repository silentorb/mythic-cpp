#pragma once

#include "haft/Input_Configuration.h"

using namespace haft;

namespace laboratory {
#define ACTION(name) static Action *name;

  class Actions {
  public:
#include "action-definitions.h"

      static void initialize(haft::Input_Configuration &config) {
#undef ACTION
#define ACTION(name) name = &config.add_action(#name);
#include "action-definitions.h"
      }
  };
}
//#undef ACTION
//#define ACTION(name) #name,
//  const char*Action_Names [] = {
//#include "action-definitions.h"
//    NULL
//  };
//}