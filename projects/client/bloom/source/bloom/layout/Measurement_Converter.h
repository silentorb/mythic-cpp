#pragma once

#include "dllexport.h"
#include "Measurement.h"
#include "glm/vec2.hpp"

using namespace glm;

namespace bloom {

  class MYTHIC_EXPORT Measurement_Converter {
      vec2 dimensions;
      float scale;

      void update_scale() {
        auto longest = dimensions.x > dimensions.y
                       ? dimensions.x
                       : dimensions.y;

        scale = longest / UNIT_RESOLUTION;
      }

  public:
      Measurement_Converter(const vec2 &dimensions) : dimensions(dimensions) {
        update_scale();
      }

      vec2 convert_position(const Vector2 &position) const {
        return vec2(
          position.x.get_value() / scale,
          position.y.get_value() / scale
        );
      }

      const vec2 &get_dimensions() const {
        return dimensions;
      }

      void set_dimensions(const vec2 &value) {
        dimensions = value;
        update_scale();
      }
  };
}
