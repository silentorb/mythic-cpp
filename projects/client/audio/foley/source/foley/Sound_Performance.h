#pragma once

namespace foley {

  class Sound_Performance {
  public:
      virtual bool is_finished() const = 0;
      virtual float update_mono(float delta) = 0;
  };
}