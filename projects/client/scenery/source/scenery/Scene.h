#pragma once
#include "dllexport.h"

#include <lookinglass/Renderable.h>
#include "scenery/elements/Element.h"
#include <vector>
#include <scenery/elements/Model.h>

using namespace scenery;
using namespace lookinglass;

namespace scenery {

  class MYTHIC_EXPORT Scene : public Renderable, no_copy {
  private:
      std::vector<unique_ptr<Element>> elements;
  public:
      virtual void render(Glass &glass);
      void add(Element *element);
  };
}



