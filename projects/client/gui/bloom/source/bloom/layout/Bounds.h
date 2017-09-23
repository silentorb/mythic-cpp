#pragma once

#include "commoner/dllexport.h"
#include <glm/vec2.hpp>
#include "bloom/bloom_export.h"

using namespace glm;

namespace bloom {

  class BLOOM_EXPORT Bounds {
//      vec2 top_left;
//      vec2 bottom_right;
//
//      Bounds(const vec2 &top_left, const vec2 &bottom_right) : top_left(top_left), bottom_right(bottom_right) { }
//      Bounds(float top, float left, float bottom, float right) : top_left(vec2(top, left)), bottom_right(vec2(bottom, right)) { }

      vec2 position;
      vec2 dimensions;
      vec2 corner;

  public:

      Bounds(const vec2 &position, const vec2 &dimensions) :
        position(position), dimensions(dimensions), corner(position + dimensions) {
      }

      const vec2 &get_position() const {
        return position;
      }

      const vec2 &get_dimensions() const {
        return dimensions;
      }

      const vec2 &get_corner() const {
        return corner;
      }
  };
}