#pragma once

#include <functional>

namespace audio {

//  typedef std::function<void(float*, int)> Signal_Source;
  class MYTHIC_EXPORT Signal_Source {
  public:
      virtual void update_buffer(float *data, int length) = 0;
  };
}
