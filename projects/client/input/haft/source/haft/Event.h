#pragma once

#include "Action.h"

namespace haft {

  class Event {
      Action action;
      float value;

  public:
      Event(const Action &action, float value)
        : action(action), value(value) {}

      Action get_action() const {
        return action;
      }

      float get_value() const {
        return value;
      }
  };

}

