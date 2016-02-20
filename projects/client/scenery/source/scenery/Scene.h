#pragma once

#include "dllexport.h"

#include <lookinglass/Renderable.h>
#include "scenery/elements/Element.h"
#include <vector>
#include <scenery/elements/Model.h>

using namespace scenery;
using namespace lookinglass;

namespace scenery {

  class MYTHIC_EXPORT Scene : public Renderable, public Parent, no_copy {
  private:
      std::vector<unique_ptr<Element>> elements;

  public:
      virtual void render(Glass &glass);
      virtual void add(unique_ptr<Element>element);
      virtual bool has_transform() override;
      virtual mat4 get_transform() override;
      virtual void move_element(unique_ptr<Element> &element, Parent &destination) override;

      virtual void move_element(Element &element, Parent &destination) override;
  };
}



