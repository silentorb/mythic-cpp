#pragma once

namespace audio{

  struct Device_Settings {
      int sample_rate;
      int buffer_size;
      unsigned char channel_count;
  };

}