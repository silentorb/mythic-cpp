#pragma once

#include <vector>
#include "Trigger.h"

using namespace std;

namespace haft {
  class Device {
      string name;
      vector<Trigger *> triggers;

  public:
      Device(const string &name) : name(name) { }

      void add_trigger(Trigger *trigger) {
        triggers.push_back(trigger);
      }
  };

}
