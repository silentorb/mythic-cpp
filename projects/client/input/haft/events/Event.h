#pragma once

#include "Action.h"

namespace haft {

  class Event {
      Action &action;

  public:

      Event(Action &action)
        : action(action) { }

      Action &get_action() const {
        return action;
      }
  };

}

