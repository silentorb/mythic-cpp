#pragma once

#include <lookinglass/Renderable.h>
#include "scenery/elements/Element.h"
#include <vector>

using namespace scenery::elements;
using namespace lookinglass;

namespace scenery {

  class Scene : public Renderable {
  private:
      std::vector<Element *>elements;
  public:
      virtual void render(Glass &glass);
  };
}



