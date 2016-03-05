#pragma once

#include "Box.h"
#include "Axis.h"

namespace bloom {

  Box::Box(const Measurement_Converter &converter) :
    converter(converter)
//    position(Vector2(Measurement(Measurement()), Measurement(0)), Vector2()) { }
  { }

  vec2 Box::get_absolute_position() const {
    if (get_parent_box())
      return get_parent_box()->get_absolute_position() + position.near.get_vec2();

    return position.near.get_vec2();
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

//  template<typename Axis>
//  Axis_Value Box::get_parent_axis_values() {
//    if (get_parent_box()) {
//      return Axis::get_cache(*get_parent_box());
//    }
//    else {
//      Axis_Value result;
//      result.near = 0;
//      result.length = result.absolute_far = Axis::get_aligned(get_converter().get_unit_dimensions());
//      return result;
//    }
//  }

  template<typename Axis>
  Axis_Value Box::calculate_axis(Axis_Value &parent_values, float margin) {
    Axis_Value result;

    const Measurement &near = Axis::get_near(*this);
    const Measurement &length = Axis::get_length(*this);
    const Measurement &far = Axis::get_far(*this);

//    Axis_Value parent_values = this->get_parent_axis_values<Axis>();

    if (length.get_type() == Measurements::stretch) {
      result.length = parent_values.length;
    }
    else {
      result.length = length.get_value();
    }

    if (near.get_type() == Measurements::stretch && far.get_type() == Measurements::units && get_parent_box() &&
        get_parent_box()->get_arrangement() == Arrangement::canvas) {
      result.absolute_far = parent_values.absolute_far - far.get_value();
      result.near = result.absolute_far - result.length;
    }
    else if (near.get_type() == Measurements::stretch && far.get_type() == Measurements::stretch) {
      auto middle = (parent_values.length - result.length) / 2;
      result.near = parent_values.near + middle;
      result.absolute_far = result.near + result.length;
    }
    else {
      result.near = parent_values.near + near.get_value();
      if (margin > result.near)
        result.near = margin;

      result.absolute_far = result.near + result.length;
      if (far.get_type() == Measurements::units)
        result.absolute_far += far.get_value();
    }

    return result;
  }

  void Box::update_absolute_dimensions(Axis_Values parent_values, vec2 margin) {
    axis_cache.x = this->calculate_axis<Horizontal_Axis>(parent_values.x, margin.x);
    axis_cache.y = this->calculate_axis<Vertical_Axis>(parent_values.y, margin.y);

    if (arrangement == Arrangement::canvas) {
      for (int i = 0; i < get_child_count(); ++i) {
        get_child_box(i).update_absolute_dimensions(axis_cache);
      }
    }
    else if (arrangement == Arrangement::down) {
      auto current = axis_cache;
      for (int i = 0; i < get_child_count(); ++i) {
        auto &child = get_child_box(i);
        child.update_absolute_dimensions(current);
//        auto offset = child.axis_cache.y.length;
        current.y.near = child.axis_cache.y.absolute_far;
//        current.y.absolute_far += offset;
      }
    }
  }
}