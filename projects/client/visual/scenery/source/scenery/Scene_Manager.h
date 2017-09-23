#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include <vector>
#include <scenery/elements/Light.h>
#include "through/Mist.h"

using namespace through;

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
      std::unique_ptr<Mist<Lighting_Data>> lighting_mist;
      std::unique_ptr<Lighting_Data> lighting;
      std::vector<std::unique_ptr<Light>> lights;

      void update_lights();

  public:
      Scene_Manager();

      void update();
      Light_Data & add_light();
  };
}