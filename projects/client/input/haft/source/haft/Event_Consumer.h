#pragma once

#include "Event.h"
#include "Generic_Event.h"

namespace haft {
  class Event_Consumer {
  public:
      virtual void add_event(Event *event) = 0;
  };
}