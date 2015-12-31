#pragma once

#include "Action.h"

namespace haft {

  class Event {
      Action &action;
      float value;

  public:

      Event(Action &action, float value = 1)
        : action(action), value(value) { }

      Action &get_action() const {
        return action;
      }

      float get_value() const {
        return value;
      }
  };

}

