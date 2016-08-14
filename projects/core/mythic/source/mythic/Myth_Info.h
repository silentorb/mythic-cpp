#pragma once
#include "commoner/dllexport.h"

#include <string>

using namespace std;

namespace mythic {

  class MYTHIC_EXPORT Mythic_Engine;

  class MYTHIC_EXPORT Myth;

  class MYTHIC_EXPORT Myth_Info {
  public:
      virtual string get_name() = 0;
      virtual Myth *fabricate(Mythic_Engine &engine) = 0;
  };
}