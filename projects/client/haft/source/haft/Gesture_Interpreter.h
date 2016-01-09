#pragma once

#include <vector>
#include "Gesture.h"
#include "Event.h"
#include "Event_Consumer.h"

using namespace std;

namespace haft {

  class Gesture_Interpreter {
  public:
      virtual void interpret(const vector<unique_ptr<Gesture>> &gestures, Event_Consumer &consumer) = 0;
  };
}