#pragma once

#include "commoner/dllexport.h"
#include "Measurement.h"
#include "Abstract_Box.h"
#include "Measurement_Converter.h"
#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include "Axis_Value_Old.h"
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

  class BLOOM_EXPORT Box_Old : no_copy {
      friend class Horizontal_Axis;

      friend class Vertical_Axis;

      void calculate_content_height();

  protected:
      Vector4 position;
      Vector2 dimensions;
      const Measurement_Converter &converter;
      Arrangement arrangement = Arrangement::canvas;
      Axis_Values_Old axis_cache;
      Axis_Values_Old axis_cache_inner;
      shared_ptr<Axis_Values_Old> clip_bounds;
      Measurement spacing = {Measurements::pixel, 0};
      float content_height;

      template<typename Axis>
      void apply_padding(Axis_Value_Old &value,  const Vector4 & padding);
      void apply_padding(Axis_Values_Old &values);
      void set_children_clipping(shared_ptr<Axis_Values_Old> &bounds);

      virtual void modify_inner() = 0;
      virtual bool clips_children() = 0;
  public:
      int debug_id = 0;

      Box_Old(const Measurement_Converter &converter);
      virtual ~Box_Old();

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
        Box_Old::dimensions = dimensions;
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

      virtual Box_Old *get_parent_box() const = 0;

      const Measurement_Converter &get_converter() const {
        return converter;
      }

      void set_right(const Measurement &value) {
        position.far.set_x(value);
      }

      void set_left(const Measurement &value) {
        position.near.set_x(value);
      }

      void set_top(float value) {
        position.near.set_y(Measurement(value));
      }

      void set_top(int value) {
        position.near.set_y(Measurement(value));
      }

      template<typename T>
      void set_top(T value) {
        position.near.set_y(value);
      }

      void set_bottom(const Measurement &value) {
        position.far.set_y(value);
      }

      Arrangement get_arrangement() const {
        return arrangement;
      }

      void set_arrangement(Arrangement arrangement) {
        Box_Old::arrangement = arrangement;
      }

      void set_arrangement(Arrangement arrangement, float spacing) {
        Box_Old::arrangement = arrangement;
        set_spacing(Measurement(spacing));
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
      Axis_Value_Old calculate_axis(const Axis_Value_Old &parent_values, float margin) const;
      void update_axis_cache(const Axis_Values_Old &parent_values, const vec2 &margin);
      virtual void update_absolute_dimensions(const Axis_Values_Old &parent_values, const vec2 margin = vec2(0));
      virtual int get_child_count() const = 0;
      virtual Box_Old &get_child_box(int index) const = 0;

//      virtual const Measurement &get_estimated_width() const {
//        return dimensions.get_x();
//      }

      const Axis_Values_Old &get_cache() const {
        return axis_cache;
      }

      virtual Box_Style &get_box_style() = 0;

      const Measurement get_spacing() const {
        return spacing;
      }

      void set_spacing(const Measurement &spacing) {
        Box_Old::spacing = spacing;
      }

      vec2 get_parent_inner_dimensions() const;

      float get_content_height() const {
        return content_height;
      }
  };

}