#include <bloom/layout/Axis.h>
#include "Box.h"
#include <commoner/assert.h>

using namespace glm;

namespace bloom {
  namespace flowers {

    template<typename Axis>
    float Box::resolve_length(const Axis_Measurement &measurements, const glm::vec2 &parent_dimensions) {
      if (measurements.length.get_type() == Measurements::shrink)
        return 0;

      if (measurements.length.get_type() != Measurements::stretch)
        return resolve_measurement<Axis>(measurements.length, parent_dimensions);

      auto length = Axis::get(parent_dimensions);

      if (measurements.near.get_type() != Measurements::stretch)
        length -= resolve_measurement<Axis>(measurements.near, parent_dimensions);

      if (measurements.far.get_type() != Measurements::stretch)
        length -= resolve_measurement<Axis>(measurements.far, parent_dimensions);

			if (length < 0)
				return 0;

      return length;
    }

    template<typename Axis>
    float Box::resolve_margins(const glm::vec2 &parent_dimensions) {
      Axis_Measurement &measurements = Axis::get(measurement_bounds);

      auto result = 0;
      if (measurements.near.get_type() != Measurements::stretch)
        result += resolve_measurement<Axis>(measurements.near, parent_dimensions);

      if (measurements.far.get_type() != Measurements::stretch)
        result += resolve_measurement<Axis>(measurements.far, parent_dimensions);

      return result;
    }

    template<typename Axis>
    float Box::resolve_relative_position(const glm::vec2 &parent_dimensions) {
      Axis_Measurement &measurements = Axis::get(measurement_bounds);
      auto local_length = Axis::get(absolute_bounds.dimensions);

      if (measurements.near.get_type() == Measurements::stretch &&
          measurements.far.get_type() == Measurements::stretch) {
        auto parent_length = Axis::get(parent_dimensions);
        return (parent_length - local_length) / 2;
      }
      else if (measurements.near.get_type() == Measurements::stretch) {
        auto parent_length = Axis::get(parent_dimensions);
        auto far = resolve_measurement<Axis>(measurements.far, parent_dimensions);
        return parent_length - local_length - far;
      }
      else {
        return resolve_measurement<Axis>(measurements.near, parent_dimensions);
      }
    }

    glm::vec2 Box::update_dimensions(const glm::vec2 &parent_bounds) {
      auto &length = absolute_bounds.dimensions;
      length.x = resolve_length<Horizontal_Axis>(measurement_bounds.x, parent_bounds);
      length.y = resolve_length<Vertical_Axis>(measurement_bounds.y, parent_bounds);

      vec2 full_length = length;
      if (debug_id == 300)
        int k = 0;

      int iterations = 0;
      if (child) {
        bool changed;
        do {
          changed = false;
          if (measurement_bounds.x.length.get_type() == Measurements::shrink) {
            int k = 0;
          }
					vec2 content_length = child->update_dimensions(length); // child->affects_parent_dimensions()
//                                ? child->update_dimensions(length)
//                                : vec2();

          if (iterations > 8) {
            int k = 0;
          }

          if (iterations++ > 10) {
            return full_length;
            Assert(false);
            break;
          }

          if (measurement_bounds.x.length.get_type() == Measurements::shrink) {
            if (length.x != content_length.x) {
              length.x = content_length.x;
              changed = true;
            }
            full_length.x = length.x + resolve_margins<Horizontal_Axis>(parent_bounds);
          }

          if (measurement_bounds.y.length.get_type() == Measurements::shrink) {
            if (length.y != content_length.y) {
              length.y = content_length.y;
              changed = true;
            }
            full_length.y = length.y + resolve_margins<Vertical_Axis>(parent_bounds);
          }
          changed = false;

        } while (changed);
      }

      return full_length;
    }

    void Box::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
//      if (debug_id == 100) {
//        int k = 0;
//      }
      relative_position.x = resolve_relative_position<Horizontal_Axis>(parent_dimensions);
      relative_position.y = resolve_relative_position<Vertical_Axis>(parent_dimensions);

      absolute_bounds.position = relative_position + parent_position;

      if (child) {
        child->update_position(absolute_bounds.position, absolute_bounds.dimensions);
      }
    }
  }
}