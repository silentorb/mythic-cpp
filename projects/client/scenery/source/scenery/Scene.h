#pragma once
#include "dllexport.h"

#include <lookinglass/Renderable.h>
#include "scenery/elements/Element.h"
#include <vector>
#include <scenery/elements/Model.h>

using namespace scenery::elements;
using namespace lookinglass;

namespace scenery {

  class MYTHIC_EXPORT Scene : public Renderable {
  private:
      std::vector<Element *> elements;
  public:
      virtual void render(Glass &glass);
      void add(elements::Element *element);
  };
}



