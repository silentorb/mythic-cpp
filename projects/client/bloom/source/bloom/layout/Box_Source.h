#pragma once

#include "Box.h"
#include "Axis.h"

namespace bloom {

  Box::Box(const Measurement_Converter &converter) :
    converter(converter)
//    position(Vector2(Measurement(Measurement()), Measurement(0)), Vector2()) { }
  { }

  Box::~Box() { }

  vec2 Box::get_parent_dimensions() const {
    auto parent_box = get_parent_box();
    if (parent_box)
      return parent_box->get_absolute_dimensions();
    else
      return get_converter().get_pixel_dimensions();
  }

//  vec2 Box::get_absolute_position() const {
//
//    auto parent_box = get_parent_box();
//    if (parent_box) {
//      return parent_box->get_absolute_position() + position.near.get_vec2(parent_box->get_absolute_dimensions());
//    }
//
//    return position.near.get_vec2();
//  }

  vec2 Box::get_absolute_dimensions() const {
    return vec2(axis_cache.x.length, axis_cache.y.length);
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
      return Axis::get_aligned(box.get_parent_dimensions());
    }
  }

  template<typename Axis>
  float Box::get_content_length(float initial_length, float near) const {
    if (initial_length != 0)
      return initial_length;

    float current_length = 0;
    for (int i = 0; i < get_child_count(); ++i) {
      auto &child = get_child_box(i);
      auto child_far = Axis::get_cache(child).absolute_far;
      auto temp_length = child_far - near;
      if (temp_length > current_length)
        current_length = temp_length;
    }

    return current_length;
  }


  template<typename Axis>
  Axis_Value Box::calculate_axis(const Axis_Value &parent_values, float margin) const {
    Axis_Value result;

    const Measurement &near = Axis::get_near(*this);
    const Measurement &length = Axis::get_length(*this);
    const Measurement &far = Axis::get_far(*this);

    auto parent_dimensions = get_parent_dimensions();
    result.near = near.resolve<Axis>(parent_dimensions, converter);
    result.length = length.resolve<Axis>(parent_dimensions, converter);
    result.absolute_far = far.resolve<Axis>(parent_dimensions, converter);

//    Axis_Value parent_values = this->get_parent_axis_values<Axis>();

    auto arrangement = get_parent_box()
                       ? get_parent_box()->get_arrangement()
                       : Arrangement::canvas;

    if (arrangement == Arrangement::down && Axis::get_index() == 1) {
      result.near = parent_values.near + result.near;
      result.length = get_content_length<Axis>(result.length, result.near);
      result.absolute_far = result.near + result.length;
      return result;
    }

    if (length.get_type() == Measurements::stretch) {
      result.length = parent_values.length;
    }
//    else {
//      result.length = length.get_value(parent_values.length);
//    }

    if (near.get_type() == Measurements::stretch && far.get_type() != Measurements::stretch &&
        arrangement == Arrangement::canvas) {
      result.absolute_far = parent_values.absolute_far - result.absolute_far;
      result.near = result.absolute_far - result.length;
    }
    else if (near.get_type() == Measurements::stretch && far.get_type() == Measurements::stretch) {
      auto middle = (parent_values.length - result.length) / 2;
      result.near = parent_values.near + middle;
      result.absolute_far = result.near + result.length;
    }
    else if (near.get_type() != Measurements::stretch && length.get_type() == Measurements::stretch &&
             far.get_type() != Measurements::stretch) {

      result.near = parent_values.near + result.near;
      result.absolute_far = parent_values.absolute_far - result.absolute_far;
      result.length = result.absolute_far - result.near;
    }
    else {
      result.near = parent_values.near + result.near;
      if (margin > result.near)
        result.near = margin;

      result.absolute_far = result.near + result.length;
      if (far.get_type() == Measurements::units)
        result.absolute_far += result.absolute_far;
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
//      current.y.length = 0;
//      current.y.absolute_far = current.y.near;
      int temp = get_child_count();
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