#include "Tuning_Event_Recorder.h"
#include "Event_Data.h"

namespace tuning {

  Tuning_Event_Recorder::Tuning_Event_Recorder(Event_Data &destination) :
    destination(destination) { }

  void Tuning_Event_Recorder::add_event(aura::Event *event) {
    event->set_absolute_start(current_time);
    destination.add_event(event);
  }

  void Tuning_Event_Recorder::update(float delta) {
    current_time += delta;
  }

}