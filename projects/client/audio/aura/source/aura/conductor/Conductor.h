#pragma once

#include "dllexport.h"
#include "Buffer_Manager.h"
#include <stack>

namespace audio {
  struct Device_Settings;
}

using namespace std;

namespace aura {

  class MYTHIC_EXPORT Conductor {
      int sample_rate;
      int buffer_size;
      unsigned char channel_count;
      Buffer_Manager buffer_manager;

  public:

      Conductor(audio::Device_Settings &device_settings);

      int get_sample_rate() const {
        return sample_rate;
      }

      int get_buffer_size() const {
        return buffer_size;
      }

      unsigned char get_channel_count() const {
        return channel_count;
      }

      Buffer_Manager &get_buffer_manager() {
        return buffer_manager;
      }
  };
}