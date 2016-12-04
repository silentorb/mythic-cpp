#pragma once

#include "Gesture.h"
#include "Event.h"
#include "Event_Consumer.h"
#include "Gesture_Container.h"

namespace haft {

  class Gesture_Interpreter {
  public:
      virtual void interpret(const Gesture_Container &gestures, Event_Consumer &consumer) = 0;
  };
}