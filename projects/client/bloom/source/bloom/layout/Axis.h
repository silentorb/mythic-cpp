#pragma once

#include "Measurement.h"
#include "Box.h"

namespace bloom {

  class Vertical_Axis;

  class Horizontal_Axis  {
  public:
      static const Measurement &get_near(const Box &box) {
        return box.get_position().x;
      }

      static const Measurement &get_length(const Box &box) {
        return box.get_dimensions().x;
      }

      static const Measurement &get_far(const Box &box) {
        return box.get_corner().x;
      }

      static const float get_aligned(const vec2 &value) {
        return value.x;
      }

      static const Axis_Value &get_cache(const Box &box) {
        return box.axis_cache.x;
      }

      static const int get_index() {
        return 0;
      }

      using other = Vertical_Axis;
  };

  class Vertical_Axis  {
  public:
      static const Measurement &get_near(const Box &box) {
        return box.get_position().y;
      }

      static const Measurement &get_length(const Box &box) {
        return box.get_dimensions().y;
      }

      static const Measurement &get_far(const Box &box) {
        return box.get_corner().y;
      }

      static const float get_aligned(const vec2 &value) {
        return value.y;
      }

      static const Axis_Value &get_cache(const Box &box) {
        return box.axis_cache.y;
      }

      static const int get_index() {
        return 1;
      }

      using other = Horizontal_Axis;
  };

}