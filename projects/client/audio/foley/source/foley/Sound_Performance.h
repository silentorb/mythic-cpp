#pragma once

namespace foley {

  class Sound_Performance {
  public:

      virtual float update_mono(float delta) = 0;
  };
}