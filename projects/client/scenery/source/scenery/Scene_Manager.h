#pragma once

#include "dllexport.h"
#include <memory>
#include "lookinglass/through/Mist.h"

using namespace std;
using namespace lookinglass::through;

namespace lookinglass {
  class House;
}

namespace scenery {

  struct Lighting_Data {

  };

  class MYTHIC_EXPORT Scene_Manager {
      unique_ptr<Mist<Lighting_Data>> lighting_mist;
  public:
      Scene_Manager(lookinglass::House &house);
  };
}