#pragma once

#include<vector>
#include<memory>
#include "Event.h"
#include "Gesture.h"
#include "Event_Consumer.h"
#include "Gesture_Container.h"
#include <glm/vec2.hpp>
#include <algorithm>

using namespace glm;

namespace haft {

  class Input_State : public Event_Consumer {
      std::vector<Gesture> gestures;
      std::vector<Event> events;
      ivec2 position;
      Input_State *previous;

  public:

      Input_State() {}

      Input_State(const Input_State &) = delete;

      void add_event(const Event &event) override {
        events.push_back(event);
      }

      void add_event(Action action, float value = 1) {
        events.push_back({action, value});
      }

      const Event *get_event(const Action &action) const {
        for (auto &event: events) {
          if (event.get_action() == action)
            return &event;
        }

        return nullptr;
      }

      const std::vector<Event> &get_events() const {
        return events;
      }

//      std::vector<Event>>::const_iterator events_begin() const {
//        return events.begin();
//      }
//
//      std::vector<std::unique_ptr<Event>>::const_iterator events_end() const {
//        return events.end();
//      }

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
        auto current_event = get_event(action);
        return current_event /*&& !current_event->was_handled()*/ && !previous->get_event(action);
      }

      void set_handled(const Action &action) const {
//        get_event(action)->set_handled(true);
      }

      void clear_events() {
        events.clear();
      }

      int get_event_count() const {
        return events.size();
      }

      const std::vector<Gesture> &get_gestures() const {
        return gestures;
      }

      void add_gesture(const Gesture gesture) {
        gestures.push_back(gesture);
      }

      void add_gesture(Gesture_Type action, ivec2 position) {
        gestures.push_back({action, position});
      }

      void clear_gestures() {
        gestures.clear();
      }

      bool has_gesture(Gesture_Type action) {
        for (auto &gesture: gestures) {
          if (gesture.action == action)
            return true;
        }
        return false;
      }
  };
}