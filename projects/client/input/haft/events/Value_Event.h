#pragma once

#include "Action.h"
#include "Event.h"

namespace haft {

  class Value_Event: public Event {
            float value;

  public:

      Value_Event(Action &action, float value = 1)
        : Event(action), value(value) { }

      float get_value() const {
        return value;
      }
  };

}

