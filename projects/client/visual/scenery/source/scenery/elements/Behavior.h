#pragma once

#include <functional>
#include "Simple_Element.h"

namespace scenery {

  template<typename T>
  class MYTHIC_EXPORT Behavior : public Simple_Element {
      const function<void(float, T &)> on_update;

  public:
      Behavior(const function<void(float, T &)> &on_update) : on_update(on_update) {}

      virtual void update(float delta) override {
        on_update(delta, *dynamic_cast<T*>(parent));
      }
  };
}