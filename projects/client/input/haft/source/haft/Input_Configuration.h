#pragma once


#include <memory>
#include <vector>
#include "Device.h"

namespace haft {

	class Input_Configuration {
      std::vector<std::unique_ptr<Device>> devices;
      std::vector<std::unique_ptr<Action>> actions;

      Input_Configuration(Input_Configuration const &) = delete;
      void operator=(Input_Configuration const &) = delete;

  public:

			Input_Configuration() {}

      void add_device(Device *device) {
        devices.push_back(std::unique_ptr<Device>(device));
      }

      void add_action(Action *action) {
        actions.push_back(std::unique_ptr<Action>(action));
      }

//      Action &add_action(const std::string &name) {
//        auto action = new Action(actions.size(), name);
//        actions.push_back(std::unique_ptr<Action>(action));
//        return *action;
//      }

      Device &get_device(int index) const {
        return *devices[index];
      }

      Device *get_device(const std::string name) const;

//      Action &get_action(const std::string name) const {
//        for (auto &action: actions) {
//          if (action->get_name() == name)
//            return *action;
//        }
//
//        throw runtime_error("Invalid action " + string(name));
//      }
  };
}