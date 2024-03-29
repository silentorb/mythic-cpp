#include "Measurement.h"
#include "Axis.h"

using namespace glm;

namespace bloom {

  float Measurement::pixel_scale = 1;

  template<typename Axis>
  float Measurement::resolve(const vec2 &parent_dimensions,
                             const Measurement_Converter &converter) const {

    if (get_type() == Measurements::stretch) {
      return 0;
    }

    else {

      auto value = static_cast<const Measurement *>(this)->get_value();

      switch (get_type()) {
        case Measurements::pixel:
          return value * Measurement::pixel_scale * UNIT_RESOLUTION / Axis::get(converter.get_pixel_dimensions());

        case Measurements::percent:
          return value * Axis::get(parent_dimensions) / 100;

        case Measurements::percent_perpendicular:
          return value * Axis::get_perpendicular(parent_dimensions) / 100;

        case Measurements::vertical_units:
          return value * converter.get_pixel_dimensions().y / 100;

        default:
          return value;
      }
    }
  }

  glm::vec2 Vector2::get_vec2(const glm::vec2 &parent_dimensions, const Measurement_Converter &converter) const {
    return glm::vec2(x.resolve<Horizontal_Axis>(parent_dimensions, converter),
                     y.resolve<Vertical_Axis>(parent_dimensions, converter));
  }
}