#pragma once

#include "Measurement.h"
#include "Box.h"

namespace bloom {
//
//  class Axis {
//  public:
//      virtual Measurement &get_near(Box &box) = 0;
//      virtual Measurement &get_length(Box &box) = 0;
//      virtual Measurement &get_far(Box &box) = 0;
//  };
//
//  class Horizontal_Axis : public Axis {
//  public:
//      virtual Measurement &get_near(Box &box) override {
//        return box.get_position().x;
//      }
//
//      virtual Measurement &get_length(Box &box) override {
//        return box.get_dimensions().x;
//      }
//
//      virtual Measurement &get_far(Box &box) override {
//        return box.get_corner().x;
//      }
//  };
//
//
//  class Vertical_Axis : public Axis {
//  public:
//      virtual Measurement &get_near(Box &box) override {
//        return box.get_position().y;
//      }
//
//      virtual Measurement &get_length(Box &box) override {
//        return box.get_dimensions().y;
//      }
//
//      virtual Measurement &get_far(Box &box) override {
//        return box.get_corner().y;
//      }
//  };


//  class Axis {
//  };

  struct Axis_Value {
      float near, length, absolute_far;
  };

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

  };

}