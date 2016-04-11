#include <audio/Device_Settings.h>
#include "Engineer.h"

namespace aura {

  Engineer::Engineer(const audio::Device_Settings &device_settings) :
    buffer_manager(device_settings.buffer_size, 4),
    sample_rate(device_settings.sample_rate),
    buffer_size(device_settings.buffer_size),
    channel_count(device_settings.channel_count) {
  }


}