#include <bloom/layout/near_and_far.h>
#include "Box.h"
#include "bloom/layout/Axis.h"

using namespace glm;

namespace bloom {
  namespace flowers {

    template<typename Axis>
    void Box::fit_to_content(const Axis_Measurement &measurements, Axis_Value &relative_bounds,
                             const glm::vec2 &parent_dimensions, float content_length) {

      assert(measurements.near.get_type() == Measurements::stretch ||
             measurements.far.get_type() == Measurements::stretch);

      if (measurements.far.get_type() == Measurements::stretch) {
        if (measurements.near.get_type() == Measurements::stretch &&
            measurements.length.get_type() == Measurements::stretch) {

          relative_bounds.near = (Axis::get(parent_dimensions) - content_length) / 2;
          relative_bounds.far = relative_bounds.near + content_length;
        }
        else {
          relative_bounds.far = relative_bounds.near + content_length;
        }
      }
      else {
        relative_bounds.near = relative_bounds.far - content_length;
      }

    }

    template<typename Axis>
    float Box::resolve_length(const Axis_Measurement &measurements, const glm::vec2 &parent_dimensions) {
      if (measurements.length.get_type() != Measurements::stretch)
        return resolve_measurement<Axis>(measurements.length, parent_dimensions);

      auto length = Axis::get(parent_dimensions);

      if (measurements.near.get_type() != Measurements::stretch)
        length -= resolve_measurement<Axis>(measurements.near, parent_dimensions);

      if (measurements.far.get_type() != Measurements::stretch)
        length -= resolve_measurement<Axis>(measurements.far, parent_dimensions);

      return length;
    }

    template<typename Axis>
    Box::Fit_To_Content Box::resolve_relative_bounds(const Axis_Measurement &measurements,
                                                     const glm::vec2 &parent_dimensions,
                                                     Axis_Value &relative_bounds) {

      relative_bounds.near = resolve_measurement<Axis>(measurements.near, parent_dimensions);
      relative_bounds.far = resolve_measurement<Axis>(measurements.far, parent_dimensions);

      if (measurements.near.get_type() == Measurements::stretch) {
        if (measurements.far.get_type() == Measurements::stretch) {
          auto length = resolve_measurement<Axis>(measurements.length, parent_dimensions);
//          if (Axis::get(parent_dimensions).stretches) {
          if (measurements.length.get_type() != Measurements::stretch) {
            auto parent_length = Axis::get(parent_dimensions);
            relative_bounds.near = (parent_length - length) / 2;
            relative_bounds.far = relative_bounds.near + length;
          }
          else {
            relative_bounds.far = Axis::get(parent_dimensions);
            return Fit_To_Content::yes;
          }
        }
        else {
          relative_bounds.near = Axis::get(parent_dimensions)
                                 - resolve_measurement<Axis>(measurements.length, parent_dimensions) -
                                 relative_bounds.far;
        }
      }
      else if (measurements.far.get_type() == Measurements::stretch) {
        if (measurements.length.get_type() == Measurements::stretch) {
          relative_bounds.far = Axis::get(parent_dimensions);
          return Fit_To_Content::yes;
//          relative_bounds.far = relative_bounds.near + calculate_content_length<Axis>();
        }
        else {
          relative_bounds.far =
            resolve_measurement<Axis>(measurements.length, parent_dimensions) + relative_bounds.near;
        }
      }
      else {
        // Nothing to do.
      }

      return Fit_To_Content::no;
    }

    glm::vec2 Box::update_dimensions(const glm::vec2 &parent_bounds) {
      auto &length = absolute_bounds.dimensions;
      length.x = resolve_length<Horizontal_Axis>(measurement_bounds.x, parent_bounds);
      length.y = resolve_length<Vertical_Axis>(measurement_bounds.y, parent_bounds);

      if (children.size() > 0) {
        auto content_length = process_children(children, length);

        if (measurement_bounds.x.length.get_type() == Measurements::stretch) {
//          fit_to_content<Horizontal_Axis>(measurement_bounds.x, relative_bounds.x, parent_bounds, content_length.x);
          length.x = content_length.x;
        }

        if (measurement_bounds.y.length.get_type() == Measurements::stretch) {
//          fit_to_content<Vertical_Axis>(measurement_bounds.y, relative_bounds.y, parent_bounds, content_length.y);
          length.y = content_length.y;
        }

//        if (fit_x == Box::Fit_To_Content::yes || fit_y == Box::Fit_To_Content::yes)
//          process_children(children, this_dimensions);
      }

      return length;
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
//      else if (measurements.far.get_type() == Measurements::stretch) {
////        relative.near = resolve_measurement<Axis>(measurements.near, parent_dimensions);
////        relative.far = local_length + relative.far;
//      }
      else {
        return resolve_measurement<Axis>(measurements.near, parent_dimensions);
//        relative.near = resolve_measurement<Axis>(measurements.near, parent_dimensions);
//        relative.far = resolve_measurement<Axis>(measurements.far, parent_dimensions);
      }
    }

    void Box::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      relative_position.x = resolve_relative_position<Horizontal_Axis>(parent_dimensions);
      relative_position.y = resolve_relative_position<Vertical_Axis>(parent_dimensions);

      absolute_bounds.position = relative_position + parent_position;

      for (auto &child: children) {
        child->update_position(absolute_bounds.position, absolute_bounds.dimensions);
      }
    }

    glm::vec2 process_children(vector<unique_ptr<Flower>> &children, const glm::vec2 &parent_dimensions) {
      vec2 content_length;
      for (auto &child: children) {
        auto child_bounds = child->update_dimensions(parent_dimensions);
        if (content_length.x < child_bounds.x)
          content_length.x = child_bounds.x;

        if (content_length.y < child_bounds.y)
          content_length.y = child_bounds.y;
      }

      return content_length;
    }

  }
}