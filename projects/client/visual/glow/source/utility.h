#pragma once
#include <string>

namespace glow {

#if DEBUG_GLOW
  void check_error(const std::string &message);
#else
 inline void check_error(const std::string &message) {}
#endif

}
