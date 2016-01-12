#include <stdexcept>
#include "Device.h"

namespace haft {

  Device::Device(const string &name, initializer_list<Trigger *> triggers) : name(name) {
    for (auto trigger : triggers) {
      add_trigger(trigger);
    }
  }

  Trigger *Device::get_trigger(const string trigger_name) const {
    for (auto &trigger: triggers) {
      if (trigger->get_name() == trigger_name)
        return trigger.get();
    }

//    throw runtime_error(string("Invalid trigger name ") + trigger_name + ".");
  }
}
