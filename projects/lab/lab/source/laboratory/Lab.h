#pragma once

#include "mythic/Myth.h"
#include <string>

namespace laboratory {

  class Lab : public mythic::Myth {
  public:
      std::string get_name() { return "lab"; }
  };
}