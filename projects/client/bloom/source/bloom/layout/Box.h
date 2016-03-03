#pragma once

#include "dllexport.h"
#include "Measurement.h"
#include "Abstract_Box.h"
#include "Measurement_Converter.h"
#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include "Axis_Value.h"

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

  class Box : no_copy {
      friend class Horizontal_Axis;
      friend class Vertical_Axis;

  protected:
      Vector2 dimensions;
      Vector2 position;
      Vector2 far;
      const Measurement_Converter &converter;
      Arrangement arrangement = Arrangement::canvas;

      Axis_Value absolute_horizontal;
      Axis_Value absolute_vertical;

      inline Measurement *get_properties() {
        return &dimensions.x;
      }

      template<typename Axis>
      Axis_Value get_parent_axis_values();

      template<typename Axis>
      Axis_Value calculate_axis();

  public:
      Box(const Measurement_Converter &converter);

      const Vector2 &get_position() const {
        return position;
      }

      void set_position(const Vector2 &value) {
        position = value;
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
        return far;
      }

      void set_corner(const Vector2 &corner) {
        Box::far = corner;
      }

      virtual Box *get_parent_box() const = 0;

      const Measurement_Converter &get_converter() const {
        return converter;
      }

      void set_right(const Measurement & value){
        far.x = value;
      }

      void set_left(const Measurement & value){
        position.x = value;
      }

      void set_top(const Measurement & value){
        position.y = value;
      }

      void set_bottom(const Measurement & value){
        far.y = value;
      }

      Arrangement get_arrangement() const {
        return arrangement;
      }

      void set_arrangement(Arrangement arrangement) {
        Box::arrangement = arrangement;
      }

      void set_width(Measurement value) {
        dimensions.x = value;
      }

      void update_absolute_dimensions();
  };

}