#include "Input_Configuration.h"

namespace haft {

  Device &Input_Configuration::get_device(const string name) const {
    for (auto &device: devices) {
      if (device->get_name() == name)
        return *device;
    }

    throw runtime_error(string("Invalid device name ") + name + ".");
  }
}