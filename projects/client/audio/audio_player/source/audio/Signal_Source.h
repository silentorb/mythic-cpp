#pragma once
#include <functional>

namespace audio {

  typedef std::function<void(float*, int)> Signal_Source;
}
