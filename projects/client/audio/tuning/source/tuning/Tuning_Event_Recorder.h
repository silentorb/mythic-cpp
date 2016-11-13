#pragma once

#include <aura/sequencing/Event_Recorder.h>
#include "commoner/dllexport.h"
#include "aura/sequencing/Event.h"

namespace tuning {
  class Event_Data;

  class Tuning_Event_Recorder : public aura::sequencing::Event_Recorder {
      Event_Data &destination;
      double current_time = 0;

  public:
      Tuning_Event_Recorder(Event_Data &destination);
      void add_event(aura::sequencing::Event *event);
      void update(float delta);
  };
}