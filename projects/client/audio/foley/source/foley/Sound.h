#pragma once

namespace foley {

  class Sound {
  public:
      virtual void set_volume(float value) = 0;
      virtual float get_volume() const = 0;
      virtual float update_mono(float delta) const = 0;
  };
}