#pragma once

#include<vector>
#include<memory>
#include "Event.h"
#include "Gesture.h"
#include "Event_Consumer.h"
#include "Gesture_Container.h"
#include <glm/glm.hpp>
#include <algorithm>

using namespace std;
using namespace glm;

namespace haft {

  class Input_State : public Event_Consumer, public Gesture_Container {
      vector<unique_ptr<Gesture>> gestures;
      vector<unique_ptr<Event>> events;
      ivec2 position;
      Input_State *previous;

      Input_State(const Input_State &) = delete;

  public:

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

      vector<unique_ptr<Event>>::const_iterator events_begin() const {
        return events.begin();
      }

      vector<unique_ptr<Event>>::const_iterator events_end() const {
        return events.end();
      }

      const ivec2 &get_position() const {
        return position;
      }

      void set_position(const ivec2 &position) {
        Input_State::position = position;
      }

      Input_State *get_previous() const {
        return previous;
      }

      void set_previous(Input_State *previous) {
        this->previous = previous;
      }

      bool just_pressed(const Action &action) const {
        return get_event(action) && (!previous || !previous->get_event(action));
      }

      void remove_event(const Action &action) {
        for (auto &event: events) {
          if (&event->get_action() == &action) {
            int offset = std::find_if(events.begin(), events.end(), [&](unique_ptr<Event> const &item) {
              return item.get() == event.get();
            }) - events.begin();

            events.erase(events.begin() + offset);
            return;
          }
        }
      }
      
      void clear_events() {
          events.clear();
      }
  };
}