#include <bloom/layout/near_and_far.h>
#include "Box.h"
#include "bloom/layout/Axis.h"

namespace bloom {
  namespace flowers {

//    void Box::update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) {
//      for (auto &child : children) {
//        child->update_layout(measurement_bounds, absolute_bounds);
//      }
//    }

    const Axis_Values &Box::get_absolute_bounds() {
      return absolute_bounds;
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

//    template<typename Axis, typename Side>
//    float Box::resolve_side_value(const Axis_Measurement &measurements, const Parent_Dimensions &parent_dimensions) {
//      if (Side::get(measurements).get_type() == Measurements::stretch) {
//
//      }
//      else {
//        return resolve_value<Axis>(Side::get(measurements), parent_dimensions);
//      }
//    }

    template<typename Axis>
    void Box::resolve_relative_bounds(const Axis_Measurement &measurements, const Parent_Dimensions &parent_dimensions,
                                      Axis_Value &relative_bounds) {

//      relative_bounds.near = resolve_side_value<Axis, Near>(measurements, parent_dimensions);
//      relative_bounds.far = resolve_side_value<Axis, Far>(measurements, parent_dimensions);

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
        relative_bounds.far = resolve_value<Axis>(measurements.length, parent_dimensions) + relative_bounds.near;
      }
      else {
        // Nothing to do.
      }


//      relative_bounds.near = measurements.near.get_type() == Measurements::stretch
//                             ? 0
//                             : resolve_value<Axis>(measurements.near, parent_dimensions);
//
//      relative_bounds.far = measurements.far.get_type() == Measurements::stretch
//                            ? 0
//                            : relative_bounds.near + resolve_value<Axis>(measurements.length, parent_dimensions);

    }

//    template<typename Axis>
//    void Box::update_bounds(const Parent_Bounds &parent_bounds) {
//      resolve_relative_bounds<Axis>(Axis::get(measurement_bounds), Axis::get(parent_bounds).dimensions, Axis::get(relative_bounds));
//      Axis::get(absolute_bounds) = Axis::get(relative_bounds) + Axis::get(parent_bounds).near;
//    }

    void Box::update_layout(const Parent_Dimensions &parent_bounds) {
//      update_bounds<Horizontal_Axis>(parent_bounds);
//      update_bounds<Vertical_Axis>(parent_bounds);

      resolve_relative_bounds<Horizontal_Axis>(measurement_bounds.x, parent_bounds, relative_bounds.x);
      absolute_bounds.x = relative_bounds.x + parent_bounds.x.near;

      resolve_relative_bounds<Vertical_Axis>(measurement_bounds.y, parent_bounds, relative_bounds.y);
      absolute_bounds.y = relative_bounds.y + parent_bounds.y.near;

      if (children.size() > 0) {
        auto this_dimensions = get_dimensions();
        for (auto &child: children) {
          child->update_layout(this_dimensions);
        }
      }
    }


  }
}