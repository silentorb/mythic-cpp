#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "Device.h"
#include "Gesture_Interpreter.h"
#include "Input_Source.h"

using namespace std;

namespace haft {

  class MYTHIC_EXPORT Input_Manager {
      vector<unique_ptr<Device>> devices;
      vector<unique_ptr<Action>> actions;
      vector<unique_ptr<Gesture_Interpreter>> gesture_interpreters;
      unique_ptr<Input_Source> source;
      unique_ptr<Input_State> current_state;
      unique_ptr<Input_State> previous_state;

      Input_Manager(const Input_Manager &); // no implementation
      Input_Manager &operator=(const Input_Manager &); // no implementation
  public:

      Input_Manager(Input_Source *source);

      void add_device(Device *device) {
//        devices.push_back(unique_ptr<Device>(device));
      }

      Action &add_action(int id, string name) {
        auto action = new Action(id, name);
//        actions.push_back(unique_ptr<Action>(action));
        return *action;
      }

      void add_gesture_interpreter(Gesture_Interpreter *interpreter) {
        gesture_interpreters.push_back(unique_ptr<Gesture_Interpreter>(interpreter));
      }

      const Input_State &getCurrent_state() const {
        return *current_state.get();
      }

      const Input_State &getPrevious_state() const {
        return *previous_state.get();
      }

      void update();
  };

}

