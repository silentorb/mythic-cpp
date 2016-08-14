#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include <vector>
#include <scenery/elements/Light.h>
#include "lookinglass/through/Mist.h"

using namespace std;
using namespace lookinglass::through;

namespace lookinglass {
  class House;
}

namespace scenery {
  const int MAX_LIGHTS = 8;

  struct Lighting_Data {
      Light_Data lights[MAX_LIGHTS];
      int count;
  };

  class MYTHIC_EXPORT Scene_Manager {
      unique_ptr<Mist<Lighting_Data>> lighting_mist;
      unique_ptr<Lighting_Data> lighting;
      vector<unique_ptr<Light>> lights;

      void update_lights();
  public:
      Scene_Manager(lookinglass::House &house);

      void update();
      Light_Data & add_light();
  };
}