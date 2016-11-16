#pragma once

#include "Single_Parent.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Box : public Single_Parent {

        Axis_Measurements measurement_bounds = {
          {{Measurements::stretch, 0}, {Measurements::stretch, 0}, {Measurements::stretch, 0}},
          {{Measurements::stretch, 0}, {Measurements::stretch, 0}, {Measurements::stretch, 0}},
        };

        Axis_Values absolute_bounds = {
          {0, 0},
          {0, 0}
        };

        glm::vec2 relative_position;

        template<typename Axis>
        float resolve_length(const Axis_Measurement &measurements,
                             const glm::vec2 &parent_dimensions);

        template<typename Axis>
        float resolve_relative_position(const glm::vec2 &parent_dimensions);

        template<typename Axis>
        float resolve_margins(const glm::vec2 &parent_dimensions);

    public:
        Box() {}

        virtual ~Box() {}

        virtual const string get_class_name() const override {
          return "Box";
        }

        virtual bool affects_parent_dimensions() const override {
          return true;
        }

        virtual const Axis_Values &get_absolute_bounds() const override {
          return absolute_bounds;
        }

        void set_left(const Measurement measurement) {
          measurement_bounds.x.near = measurement;
        }

        void set_top(const Measurement measurement) {
          measurement_bounds.y.near = measurement;
        }

        void set_right(const Measurement measurement) {
          measurement_bounds.x.far = measurement;
        }

        void set_bottom(const Measurement measurement) {
          measurement_bounds.y.far = measurement;
        }

        void set_width(const Measurement measurement) {
          measurement_bounds.x.length = measurement;
        }

        void set_height(const Measurement measurement) {
          measurement_bounds.y.length = measurement;
        }

        void set_position(const Measurement &left, const Measurement &top) {
          measurement_bounds.x.near = left;
          measurement_bounds.y.near = top;
        }

        void set_dimensions(const Measurement &width, const Measurement &height) {
          measurement_bounds.x.length = width;
          measurement_bounds.y.length = height;
        }

        void set_margins(const Measurement &value) {
          measurement_bounds.x.near = value;
          measurement_bounds.y.near = value;
          measurement_bounds.x.far = value;
          measurement_bounds.y.far = value;
        }

        void set_margins(const Measurement &horizontal, const Measurement &vertical) {
          measurement_bounds.x.near = horizontal;
          measurement_bounds.y.near = vertical;
          measurement_bounds.x.far = horizontal;
          measurement_bounds.y.far = vertical;
        }

        Axis_Measurements &get_measurements() {
          return measurement_bounds;
        }

        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_position) override;

        virtual bool get_relative_bounds(glm::vec2 &position, glm::vec2 &dimensions) override {
          position = relative_position;
          dimensions = absolute_bounds.dimensions;
          return true;
        }
    };

    template<typename Axis>
    float resolve_measurement(const Measurement &measurement, const glm::vec2 &parent_dimensions) {
      switch (measurement.get_type()) {
        case Measurements::pixel:
          return measurement.get_value() * Measurement::pixel_scale;

        case Measurements::percent:
          return measurement.get_value() * Axis::get(parent_dimensions) / 100;

        case Measurements::percent_perpendicular:
          return measurement.get_value() * Axis::other::get(parent_dimensions) / 100;

        case Measurements::stretch:
          return 0;

        default:
          throw runtime_error("Not implemented.");
      }
    }

  }
}