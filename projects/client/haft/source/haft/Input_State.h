#pragma once

#include<vector>
#include<memory>
#include "Event.h"
#include "Gesture.h"
#include "Event_Consumer.h"
#include "Gesture_Container.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace haft {

  class Input_State : public Event_Consumer, public Gesture_Container {
      vector<unique_ptr<Gesture>> gestures;
      vector<unique_ptr<Event>> events;
      Input_State(const Input_State &) = delete;
  public:
      vec2 mouse_position;

      Input_State() { }

      void add_event(Event *event) override {
        events.push_back(unique_ptr<Event>(event));
      }

      void add_event(Action &action, float value = 1) {
        events.push_back(unique_ptr<Event>(new Event(action, value)));
      }

      Gesture &get_gesture(int index) const {
        return *gestures[index];
      }

      void add_gesture(Gesture *gesture) {
        gestures.push_back(unique_ptr<Gesture>(gesture));
      }

      int get_gesture_count() const {
        return gestures.size();
      }

      Event *get_event(const Action &action) const {
        for (auto &event: events) {
          if (&event->get_action() == &action)
            return event.get();
        }

        return nullptr;
      }
  };
}