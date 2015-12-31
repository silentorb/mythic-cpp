#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "Device.h"

using namespace std;

namespace haft {

  class MYTHIC_EXPORT Input_Manager {
      vector<unique_ptr<Device>> devices;
      vector<unique_ptr<Action>> actions;

  public:

      void add_device(Device *device) {
        devices.push_back(unique_ptr<Device>(device));
      }

      Action &add_action(int id, string name) {
        auto action = new Action(id, name);
        actions.push_back(unique_ptr<Action>(action));
        return *action;
      }
  };

}

