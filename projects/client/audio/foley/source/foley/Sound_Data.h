#pragma once

#include <aura/Stroke.h>

namespace foley {

  class Sound_Data : public aura::Stroke {
  protected:
      float volume;

  public:
      Sound_Data(double duration) : aura::Stroke(duration) {}

      void set_volume(float value) {
        volume = value;
      }

      float get_volume() const {
        return volume;
      }

      virtual float update(float beat_delta) override {
        progress += beat_delta;
        return 0;
      }
  };
}