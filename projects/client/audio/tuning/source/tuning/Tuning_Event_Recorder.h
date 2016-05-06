#pragma once

#include <aura/sequencing/Event_Recorder.h>
#include "dllexport.h"
#include "aura/sequencing/Event.h"

namespace tuning {
  class Event_Data;

  class MYTHIC_EXPORT Tuning_Event_Recorder : public aura::Event_Recorder {
      Event_Data &destination;
      double current_time = 0;

  public:
      Tuning_Event_Recorder(Event_Data &destination);
      void add_event(aura::Event *event);
      void update(float delta);
  };
}