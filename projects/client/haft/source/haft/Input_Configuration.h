#pragma once

#include "dllexport.h"
#include <memory>
#include <vector>
#include "Device.h"

using namespace std;

namespace haft {

	class MYTHIC_EXPORT Input_Configuration {
      vector<unique_ptr<Device>> devices;
      vector<unique_ptr<Action>> actions;

      Input_Configuration(Input_Configuration const &) = delete;
      void operator=(Input_Configuration const &) = delete;

  public:

			Input_Configuration() {}

      void add_device(Device *device) {
        devices.push_back(unique_ptr<Device>(device));
      }

      void add_action(Action *action) {
        actions.push_back(unique_ptr<Action>(action));
      }

      Action &add_action(const string &name) {
        auto action = new Action(actions.size(), name);
        actions.push_back(unique_ptr<Action>(action));
        return *action;
      }

      Device &get_device(int index) const {
        return *devices[index];
      }

      Device &get_device(const string name) const;

      Action &get_action(const string name) const {
        for (auto &action: actions) {
          if (action->get_name() == name)
            return *action;
        }

        throw runtime_error("Invalid action " + string(name));
      }
  };
}