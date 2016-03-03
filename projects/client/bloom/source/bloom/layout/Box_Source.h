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
  Axis_Value Box::get_parent_axis_values() {
    if (get_parent_box()) {
      return Axis::get_cache(*get_parent_box());
    }
    else {
      Axis_Value result;
      result.near = 0;
      result.length = result.absolute_far = Axis::get_aligned(get_converter().get_unit_dimensions());
      return result;
    }
  }

  template<typename Axis>
  Axis_Value Box::calculate_axis() {
    Axis_Value result;

    const Measurement &near = Axis::get_near(*this);
    const Measurement &length = Axis::get_length(*this);
    const Measurement &far = Axis::get_far(*this);

    Axis_Value parent_values = this->get_parent_axis_values<Axis>();

    if (length.get_type() == Measurements::stretch) {
      result.length = parent_values.length;
    }
    else {
      result.length = length.get_value();
    }

    if (near.get_type() == Measurements::stretch && far.get_type() == Measurements::units) {
      result.absolute_far = parent_values.absolute_far - far.get_value();
      result.near = result.absolute_far - result.length;
    }
    else if (near.get_type() == Measurements::stretch && far.get_type() == Measurements::stretch) {
      auto middle = (parent_values.length - result.length) / 2;
      result.near = parent_values.near + middle;
			result.absolute_far = result.near + result.length;
    }
    else {
      result.near = near.get_value();
      result.absolute_far = result.near + result.length;
    }

    return result;
  }

  void Box::update_absolute_dimensions() {
    absolute_horizontal = this->calculate_axis<Horizontal_Axis>();
    absolute_vertical = this->calculate_axis<Vertical_Axis>();
  }

//  vec2 Box::get_absolute_dimensions() const {
//    auto x = this->calculate_axis<Horizontal_Axis>();
//    auto y = this->calculate_axis<Vertical_Axis>();
//    return vec2(
//      x.length,
//      y.length
//    );
//  }

}