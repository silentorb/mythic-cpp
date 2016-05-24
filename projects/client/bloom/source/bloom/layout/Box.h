#pragma once

#include "dllexport.h"
#include "Measurement.h"
#include "Abstract_Box.h"
#include "Measurement_Converter.h"
#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include "Axis_Value.h"
#include <memory>
#include "bloom/bloom_export.h"
#include "Box_Style.h"

using namespace std;
using namespace glm;

namespace bloom {

  enum class Box_Properties {
      width,
      height,
      left,
      top,
      right,
      bottom
  };

  const static int BOX_PROPERTY_COUNT = 6;

  enum class Arrangement {
      canvas,
      down,
      right,
      up,
      left,
  };

  class BLOOM_EXPORT Box : no_copy {
      friend class Horizontal_Axis;

      friend class Vertical_Axis;

  protected:
      Vector4 position;
      Vector2 dimensions;
      const Measurement_Converter &converter;
      Arrangement arrangement = Arrangement::canvas;
      Axis_Values axis_cache;
      Axis_Values axis_cache_inner;
      unique_ptr<Measurement> spacing;

      template<typename Axis>
      void apply_padding(Axis_Value &value,  const Vector4 & padding);
      void apply_padding(Axis_Values &values);

  public:
      int debug_id = 0;

      Box(const Measurement_Converter &converter);
      ~Box();

      const Vector2 &get_position() const {
        return position.near;
      }

      void set_position(const Vector2 &value) {
        position.near = value;
      }

      void set_position(const Measurement &left, const Measurement &top) {
        position.near = Vector2(left, top);
      }

      vec2 get_absolute_position() const;
      vec2 get_absolute_dimensions() const;

      const Vector2 &get_dimensions() const {
        return dimensions;
      }

      void set_dimensions(const Vector2 &dimensions) {
        Box::dimensions = dimensions;
      }

      void set_dimensions(const Measurement &width, const Measurement &height) {
        dimensions = Vector2(width, height);
      }

      const Vector2 &get_corner() const {
        return position.far;
      }

      void set_corner(const Vector2 &corner) {
        position.far = corner;
      }

      virtual Box *get_parent_box() const = 0;

      const Measurement_Converter &get_converter() const {
        return converter;
      }

      void set_right(const Measurement &value) {
        position.far.set_x(value);
      }

      void set_left(const Measurement &value) {
        position.near.set_x(value);
      }

      void set_left(const Simple_Measurement &value) {
        position.near.set_x(value);
      }

      void set_top(float value) {
        position.near.set_y(Simple_Measurement(value));
      }

      void set_top(int value) {
        position.near.set_y(Simple_Measurement(value));
      }

      template<typename T>
      void set_top(T value) {
        position.near.set_y(value);
      }

      void set_bottom(const Measurement &value) {
        position.far.set_y(value);
      }

      void set_bottom(const Simple_Measurement &value) {
        position.far.set_y(value);
      }

      Arrangement get_arrangement() const {
        return arrangement;
      }

      void set_arrangement(Arrangement arrangement) {
        Box::arrangement = arrangement;
      }

      template<typename T>
      void set_width(T value) {
        dimensions.set_x(value);
      }

      template<typename T>
      void set_height(T value) {
        dimensions.set_y(value);
      }

      template<typename Axis>
      float get_content_length(float initial_length, float near) const;

      vec2 get_parent_dimensions() const;

      template<typename Axis>
      Axis_Value calculate_axis(const Axis_Value &parent_values, float margin) const;
      void update_axis_cache(const Axis_Values &parent_values, const vec2 &margin);
      virtual void update_absolute_dimensions(const Axis_Values &parent_values, const vec2 margin = vec2(0));
      virtual int get_child_count() const = 0;
      virtual Box &get_child_box(int index) const = 0;

//      virtual const Measurement &get_estimated_width() const {
//        return dimensions.get_x();
//      }

      const Axis_Values &get_cache() const {
        return axis_cache;
      }

      virtual Box_Style &get_box_style() = 0;

      const Measurement *get_spacing() const {
        return spacing.get();
      }

      void set_spacing(const Measurement &spacing) {
        Box::spacing = unique_ptr<Measurement>(spacing.clone());
      }
  };

}