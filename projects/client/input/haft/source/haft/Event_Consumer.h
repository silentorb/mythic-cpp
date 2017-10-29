#pragma once

#include "Event.h"

namespace haft {
  class Event_Consumer {
  public:
      virtual void add_event(const Event &event) = 0;
  };
}