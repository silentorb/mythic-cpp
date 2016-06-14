#include "Measurement.h"
#include "Axis.h"

using namespace glm;

namespace bloom {

  Measurement::Measurement(Measurements type) : type(type) {
    static unsigned long counter = 0;
    debug_index = counter++;
    int k = 0;
  }

  template<typename Axis>
  float Measurement::resolve(const vec2 &parent_dimensions,
                             const Measurement_Converter &converter) const {

    if (get_type() == Measurements::stretch) {
      return 0;
    }
    else if (get_type() == Measurements::complex) {
      auto complex_measurement = static_cast<const Complex_Measurement *>(this);
      auto result = 0;
      for (auto &measurement: complex_measurement->get_measurements()) {
        result += measurement->resolve<Axis>(parent_dimensions, converter);
      }
      return result;
    }
    else {

      auto value = static_cast<const Simple_Measurement *>(this)->get_value();

      switch (get_type()) {
        case Measurements::pixels:
          return value * UNIT_RESOLUTION / Axis::get_aligned(converter.get_pixel_dimensions());

        case Measurements::parent_aligned:
          return value * Axis::get_aligned(parent_dimensions) / UNIT_RESOLUTION;

        case Measurements::parent_perpendicular:
          return value * Axis::get_perpendicular(parent_dimensions) / UNIT_RESOLUTION;

        case Measurements::percent:
          return value * Axis::get_aligned(parent_dimensions) / 100;

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
    return glm::vec2(x->resolve<Horizontal_Axis>(parent_dimensions, converter),
                     y->resolve<Vertical_Axis>(parent_dimensions, converter));
  }
}