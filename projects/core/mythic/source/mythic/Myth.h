#pragma once

#include <string>
//#include "lookinglass/Renderable.h"

namespace mythic {
  class Mythic_Engine;

  class Myth {
  protected:
      Mythic_Engine &engine;
      Myth(Mythic_Engine &engine);

  public:
      virtual std::string get_name() = 0;
      virtual void update(float delta);
//      virtual void render(lookinglass::Glass & glass);
  };
}