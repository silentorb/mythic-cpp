#pragma once

#include "Action.h"

namespace haft {

  class Event {
      Action &action;
      float value;
      bool handled = false;

  public:

      Event(Action &action, float value = 1)
        : action(action), value(value) { }

      Action &get_action() const {
        return action;
      }

      float get_value() const {
        return value;
      }

      bool was_handled() const {
        return handled;
      }

      void set_handled(bool handled) {
        Event::handled = handled;
      }
  };

}

