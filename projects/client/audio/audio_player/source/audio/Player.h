#pragma once

#include "commoner/dllexport.h"
#include "Sound.h"
#include "Device_Settings.h"
#include "Signal_Source.h"
#include <vector>
#include <mutex>

using namespace std;

namespace audio {

  class Speaker;

  class MYTHIC_EXPORT Player {
      friend class Speaker;

      vector<Sound> sounds;
      unique_ptr<Speaker> speaker;
      float last_delta;
      float current = 0;
      Device_Settings device_settings;
      weak_ptr<Signal_Source> source;
      void speaker_update_buffer(float *data, int length);
      mutex m;

  public:

      Player(Speaker *speaker);
      ~Player();
//      void play(Waveform &waveform);
//      void update(float delta);

      void set_source(const shared_ptr<Signal_Source> &source) {
        this->source = weak_ptr<Signal_Source>(source);
      }

      void delete_source() {
        source.reset();
      }

      const Device_Settings &get_device_settings() const {
        return device_settings;
      }
  };
}
