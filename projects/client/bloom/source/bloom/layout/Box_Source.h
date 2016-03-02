#pragma once

#include "Box.h"
#include "Axis.h"

namespace bloom {

  Box::Box(const Measurement_Converter &converter) :
    converter(converter), position(Measurement(0), Measurement(0)) { }

  vec2 Box::get_absolute_position() const {
    if (get_parent_box())
      return get_parent_box()->get_absolute_position() + position.get_vec2();

    return position.get_vec2();
  }

  template<typename Axis>
  float get_absolute_dimension(const Box &box) {
    const Measurement &length = Axis::get_length(box);
    if (length.get_type() == Measurements::stretch) {
      if (box.get_parent_box()) {
        return get_absolute_dimension<Axis>(*box.get_parent_box());
      }
      else {
        return Axis::get_aligned(box.get_converter().get_unit_dimensions());
      }
    }
    else {
      return length.get_value();
    }
  }

  template<typename Axis>
  Axis_Value get_parent_axis_values(const Box &box) {
    if (box.get_parent_box()) {
      return calculate_axis<Axis>(*box.get_parent_box());
    }
    else {
      Axis_Value result;
      result.near = 0;
      result.length = result.absolute_far = Axis::get_aligned(box.get_converter().get_unit_dimensions());
      return result;
    }
  }

  template<typename Axis>
  Axis_Value calculate_axis(const Box &box) {
    Axis_Value result;

    const Measurement &near = Axis::get_near(box);
    const Measurement &length = Axis::get_length(box);
    const Measurement &far = Axis::get_far(box);

    Axis_Value parent_values = get_parent_axis_values<Axis>(box);

    if (length.get_type() == Measurements::stretch) {
      if (box.get_parent_box()) {
        result.length = get_absolute_dimension<Axis>(*box.get_parent_box());
      }
      else {
        result.length = Axis::get_aligned(box.get_converter().get_unit_dimensions());
      }
    }
    else {
      result.length = length.get_value();
    }

    if (near.get_type() == Measurements::stretch && far.get_type() == Measurements::units) {
      result.absolute_far = parent_values.absolute_far - far.get_value();
      result.near = result.absolute_far - result.length;
    }
    else {
      result.near = near.get_value();
      result.absolute_far = result.near + result.length;
    }

    return result;
  }

  vec2 Box::get_absolute_dimensions() const {
    auto x = calculate_axis<Horizontal_Axis>(*this);
    auto y = calculate_axis<Vertical_Axis>(*this);
    return vec2(
      x.length,
      y.length
    );
  }

}