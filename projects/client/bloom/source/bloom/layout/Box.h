#pragma once

#include "dllexport.h"
#include "Measurement.h"
#include "Abstract_Box.h"
#include "Measurement_Converter.h"
#include <vector>
#include <memory>
#include <glm/vec2.hpp>

using namespace std;
using namespace glm;

namespace bloom {

  enum Box_Properties {
      width,
      height,
      left,
      top,
      right,
      bottom
  };
  const static int BOX_PROPERTY_COUNT = 6;

  template<typename T>
  class Box : no_copy, Abstract_Box<T> {
  protected:
      vector<unique_ptr<T>> children;
      T *parent = nullptr;
      Vector2 dimensions;
      Vector2 position;
      Vector2 corner;
      const Measurement_Converter &converter;

      inline Measurement *get_properties() {
        return &dimensions.x;
      }

      void set_width(Measurement &value) {
        dimensions.x = value;
      }

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
        return corner;
      }

      void set_corner(const Vector2 &corner) {
        Box::corner = corner;
      }
  };
}