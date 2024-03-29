#pragma once

#include "Buffer_Manager.h"
#include <stack>

namespace audio {
  struct Device_Settings;
}

using namespace std;

namespace aura {
  namespace engineering {

    class Engineer {
        unsigned int sample_rate;
        unsigned int buffer_size;
        unsigned char channel_count;
        Buffer_Manager buffer_manager;

    public:
        Engineer(const audio::Device_Settings &device_settings);

        unsigned int get_sample_rate() const {
          return sample_rate;
        }

        unsigned int get_buffer_byte_size() const {
          return buffer_size;
        }

        unsigned char get_channel_count() const {
          return channel_count;
        }

        Buffer_Manager &get_buffer_manager() {
          return buffer_manager;
        }

        float bytes_to_seconds(int byte_count) {
          return (float) byte_count / sizeof(float) / sample_rate / channel_count;
        }

        int bytes_to_samples(int byte_count) {
          return byte_count / sizeof(float) / channel_count;
        }

    };
  }
}