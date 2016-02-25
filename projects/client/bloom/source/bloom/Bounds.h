#pragma once

#include "dllexport.h"

using namespace glm;

namespace bloom {

  struct MYTHIC_EXPORT Bounds {
      vec2 top_left;
      vec2 bottom_right;

      Bounds(const vec2 &top_left, const vec2 &bottom_right) : top_left(top_left), bottom_right(bottom_right) { }
      Bounds(float top, float left, float bottom, float right) : top_left(vec2(top, left)), bottom_right(vec2(bottom, right)) { }
  };
}