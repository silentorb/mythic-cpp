#pragma once

#include <laboratory/display/Freeform_Camera.h>
#include "mythic/Mythic_Engine.h"

namespace scenery {
  class Scene;
}

using namespace laboratory::display;
using namespace mythic;
using namespace scenery;

namespace laboratory {

  class Architecture_Lab {
  private:
      Freeform_Camera *camera;
      Scene *scene;
      Mythic_Engine &engine;

  public:
      Architecture_Lab(Mythic_Engine &engine);
      ~Architecture_Lab();
  };
}