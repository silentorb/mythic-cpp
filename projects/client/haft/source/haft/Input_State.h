#pragma once

#include<vector>
#include<memory>
#include "Event.h"
#include "Gesture.h"
#include "Event_Consumer.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace haft {

  struct Input_State : public Event_Consumer {
      vector<unique_ptr<Event>> events;
      vector<unique_ptr<Gesture>> gestures;
      vec2 mouse_position;

      void add_event(Event *event) {
        events.push_back(unique_ptr<Event>(event));
      }
  };
}