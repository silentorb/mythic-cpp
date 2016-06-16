#pragma once

#include "Measurement.h"
#include "Box_Old.h"
#include "Parent_Dimensions.h"

namespace bloom {

  class Vertical_Axis;

  class Horizontal_Axis {
  public:
      static const Measurement &get_near(const Box_Old &box) {
        return box.get_position().get_x();
      }

      static const Measurement &get_length(const Box_Old &box) {
        return box.get_dimensions().get_x();
      }

      static const Measurement &get_far(const Box_Old &box) {
        return box.get_corner().get_x();
      }

      static const float get_aligned(const vec2 &value) {
        return value.x;
      }

      static const float get_perpendicular(const vec2 &value) {
        return value.y;
      }

      static const Measurement &get_aligned(const Vector2 &value) {
        return value.get_x();
      }

      static const Measurement &get_perpendicular(const Vector2 &value) {
        return value.get_y();
      }

      static const Axis_Value_Old &get_cache(const Box_Old &box) {
        return box.axis_cache.x;
      }

      static const int get_index() {
        return 0;
      }

      static const Parent_Dimension get(const Parent_Dimensions & parent_dimensions) {
        return parent_dimensions.x;
      }

      using other = Vertical_Axis;
  };

  class Vertical_Axis {
  public:
      static const Measurement &get_near(const Box_Old &box) {
        return box.get_position().get_y();
      }

      static const Measurement &get_length(const Box_Old &box) {
        return box.get_dimensions().get_y();
      }

      static const Measurement &get_far(const Box_Old &box) {
        return box.get_corner().get_y();
      }

      static const float get_aligned(const vec2 &value) {
        return value.y;
      }

      static const float get_perpendicular(const vec2 &value) {
        return value.x;
      }

      static const Measurement &get_aligned(const Vector2 &value) {
        return value.get_y();
      }

      static const Measurement &get_perpendicular(const Vector2 &value) {
        return value.get_x();
      }

      static const Axis_Value_Old &get_cache(const Box_Old &box) {
        return box.axis_cache.y;
      }

      static const int get_index() {
        return 1;
      }

      static const Parent_Dimension get(const Parent_Dimensions & parent_dimensions) {
        return parent_dimensions.y;
      }

      using other = Horizontal_Axis;
  };

}