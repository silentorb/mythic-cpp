#pragma once

namespace foley {

  class Sound_Data {
  protected:
      float volume;

  public:

      void set_volume(float value) {
        volume = value;
      }

      float get_volume() const {
        return volume;
      }

  };
}