#pragma once

#include <functional>
#include "Simple_Element.h"

namespace scenery {

  template<typename Parent_Type>
  class  Behavior : public Simple_Element {
      const function<void(float, Parent_Type &)> on_update;

  public:
      Behavior(const function<void(float, Parent_Type &)> &on_update) : on_update(on_update) {}

      virtual void update(float delta) override {
        on_update(delta, *dynamic_cast<Parent_Type*>(parent));
      }
  };
}