#pragma once


#include "Event.h"

namespace aura {
  namespace sequencing {

    class Event_Recorder {
    public:
        virtual void add_event(Event *event) = 0;
    };
  }
}