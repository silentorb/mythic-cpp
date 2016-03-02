#pragma once

#include "dllexport.h"
#include "Measurement.h"
#include "glm/vec2.hpp"

using namespace glm;

namespace bloom {

  class MYTHIC_EXPORT Measurement_Converter {
      vec2 pixel_dimensions;
      vec2 unit_dimensions;
      float scale;

      void update_scale() {
        auto longest = pixel_dimensions.x > pixel_dimensions.y
                       ? pixel_dimensions.x
                       : pixel_dimensions.y;

        scale = longest / UNIT_RESOLUTION;

        unit_dimensions = pixel_dimensions / scale;
      }

  public:
      Measurement_Converter(const vec2 &dimensions) : pixel_dimensions(dimensions) {
        update_scale();
      }

      vec2 convert(const Vector2 &position) const {
        return vec2(
          position.x.get_value() * scale,
          position.y.get_value() * scale
        );
      }

      vec2 convert(const vec2 &position) const {
        return vec2(
          position.x * scale,
          position.y * scale
        );
      }

      const vec2 &get_pixel_dimensions() const {
        return pixel_dimensions;
      }

      void set_pixel_dimensions(const vec2 &value) {
        pixel_dimensions = value;
        update_scale();
      }

      const vec2 &get_unit_dimensions() const {
        return unit_dimensions;
      }
  };
}
