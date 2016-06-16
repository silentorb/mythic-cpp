#include <bloom/layout/near_and_far.h>
#include "Box.h"
#include "bloom/layout/Axis.h"

namespace bloom {
  namespace flowers {

//    template<typename Axis>
//    float Box::calculate_content_length() {
//      auto length = 0;
//      auto this_dimensions = get_dimensions();
//      Axis_Value local_bounds;
//      for (auto &child: children) {
//        child->resolve_relative_bounds<Axis>(Axis::get(measurement_bounds), this_dimensions, local_bounds);
//        length += local_bounds.far;
//      }
//
//      return length;
//    }

    template<typename Axis>
    void Box::fit_to_content(const Axis_Measurement &measurements, Axis_Value &relative_bounds,
                             float content_length) {

      assert(measurements.near.get_type() == Measurements::stretch ||
             measurements.far.get_type() == Measurements::stretch);

      if (measurements.far.get_type() == Measurements::stretch) {
        relative_bounds.far = relative_bounds.near + content_length;
      }
      else {
        relative_bounds.near = relative_bounds.far - content_length;
      }

    }

    template<typename Axis>
    float Box::resolve_value(const Measurement &measurement, const Parent_Dimensions &parent_dimensions) {
      switch (measurement.get_type()) {
        case Measurements::pixel:
          return measurement.get_value();

        case Measurements::percent:
          return measurement.get_value() * Axis::get(parent_dimensions).length / 100;

        case Measurements::percent_perpendicular:
          return measurement.get_value() * Axis::other::get(parent_dimensions).length / 100;

        case Measurements::stretch:
          return 0;

        default:
          throw runtime_error("Not implemented.");
      }
    }

    template<typename Axis>
    Box::Fit_To_Content Box::resolve_relative_bounds(const Axis_Measurement &measurements,
                                                     const Parent_Dimensions &parent_dimensions,
                                                     Axis_Value &relative_bounds) {

      relative_bounds.near = resolve_value<Axis>(measurements.near, parent_dimensions);
      relative_bounds.far = resolve_value<Axis>(measurements.far, parent_dimensions);

      if (measurements.near.get_type() == Measurements::stretch) {
        if (measurements.far.get_type() == Measurements::stretch) {
          auto parent_length = Axis::get(parent_dimensions).length;
          auto length = resolve_value<Axis>(measurements.length, parent_dimensions);
          relative_bounds.near = relative_bounds.far =
            (parent_length - length) / 2;
        }
        else {
          relative_bounds.near = Axis::get(parent_dimensions).length
                                 - resolve_value<Axis>(measurements.length, parent_dimensions) - relative_bounds.far;
        }
      }
      else if (measurements.far.get_type() == Measurements::stretch) {
        if (measurements.length.get_type() == Measurements::stretch) {
          return Fit_To_Content::yes;
//          relative_bounds.far = relative_bounds.near + calculate_content_length<Axis>();
        }
        else {
          relative_bounds.far = resolve_value<Axis>(measurements.length, parent_dimensions) + relative_bounds.near;
        }
      }
      else {
        // Nothing to do.
      }

      return Fit_To_Content::no;
    }

    Axis_Values &Box::update_relative(const Parent_Dimensions &parent_bounds) {

      auto fit_x = resolve_relative_bounds<Horizontal_Axis>(measurement_bounds.x, parent_bounds, relative_bounds.x);
      auto fit_y = resolve_relative_bounds<Vertical_Axis>(measurement_bounds.y, parent_bounds, relative_bounds.y);

      vec2 content_length;

      auto this_dimensions = get_dimensions();
      for (auto &child: children) {
        auto &child_bounds = child->update_relative(this_dimensions);
        content_length.x += child_bounds.x.far;
        content_length.y += child_bounds.y.far;
      }

      if (fit_x == Box::Fit_To_Content::yes) {
        fit_to_content<Horizontal_Axis>(measurement_bounds.x, relative_bounds.x, content_length.x);
      }

      if (fit_y == Box::Fit_To_Content::yes) {
        fit_to_content<Vertical_Axis>(measurement_bounds.y, relative_bounds.y, content_length.y);
      }

      return relative_bounds;
    }

    void Box::update_absolute(const glm::vec2 &parent_position) {
      absolute_bounds.x = relative_bounds.x + parent_position.x;
      absolute_bounds.y = relative_bounds.y + parent_position.y;

      for (auto &child: children) {
        child->update_relative({absolute_bounds.x.near, absolute_bounds.y.near});
      }
    }

  }
}