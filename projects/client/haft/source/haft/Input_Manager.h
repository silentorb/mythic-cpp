#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "Device.h"
#include "Gesture_Interpreter.h"
#include "Input_Source.h"
#include "Input_Configuration.h"

using namespace std;

namespace haft {

  class MYTHIC_EXPORT Input_Manager {
      unique_ptr<Input_Configuration> config;
      vector<unique_ptr<Gesture_Interpreter>> gesture_interpreters;
      unique_ptr<Input_Source> source;
      unique_ptr<Input_State> current_state;
      unique_ptr<Input_State> previous_state;

      Input_Manager(const Input_Manager &) = delete;
  public:

      Input_Manager();

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

      Input_State &get_current_state() const {
        return *current_state.get();
      }

      Input_State &get_previous_state() const {
        return *previous_state.get();
      }

      void add_input_source(Input_Source *new_source);

      Input_Configuration &get_config() const {
        return *config;
      }

      void update();
  };

}
