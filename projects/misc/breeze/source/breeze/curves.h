#pragma once

#include <functional>

namespace breeze {
  typedef std::function<float(float)> Curve_Delegate;

  namespace curves {
    float linear(float value);
    float bezier(float value);
    float cubic(float value);
  }
}