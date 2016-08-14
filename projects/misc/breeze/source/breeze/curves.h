#pragma once

#include <functional>
#include "commoner/dllexport.h"

namespace breeze {
  typedef std::function<float(float)> Curve_Delegate;

  namespace curves {
    MYTHIC_EXPORT float linear(float value);
    MYTHIC_EXPORT float bezier(float value);
  }
}