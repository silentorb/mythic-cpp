#pragma once

#include "dllexport.h"
#include "Event.h"

namespace aura {
  namespace sequencing {

    class MYTHIC_EXPORT Event_Recorder {
    public:
        virtual void add_event(Event *event) = 0;
    };
  }
}