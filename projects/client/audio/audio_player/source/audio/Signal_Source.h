#pragma once
#include <functional>

namespace audio {

  typedef std::function<void(unsigned char*, int)> Signal_Source;
}