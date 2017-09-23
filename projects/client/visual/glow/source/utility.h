#pragma once

#include "commoner/dllexport.h"
#include<string>

namespace glow {

  using namespace std;

#if COMMONER_DEBUG
  MYTHIC_EXPORT void check_error(const char *message);
#else
 inline void check_error(const char *message) {}
#endif

}
