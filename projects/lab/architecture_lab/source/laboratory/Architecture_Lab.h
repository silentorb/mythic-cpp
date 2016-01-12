#pragma once

#include "dllexport.h"

#include "mythic/Mythic_Engine.h"

namespace scenery {
  class Scene;
}

using namespace mythic;
using namespace scenery;

namespace lookinglass {
  class House;
}

namespace laboratory {
  namespace display {
    class Freeform_Camera;
  }
  using namespace laboratory::display;

  class MYTHIC_EXPORT Architecture_Lab {
  private:
      Freeform_Camera *camera;
      Scene *scene;
      Mythic_Engine &engine;

  public:
      Architecture_Lab(Mythic_Engine &engine);
      ~Architecture_Lab();

      void initialize_lookinglass(lookinglass::House & house);
      void update(float delta);
  };
}