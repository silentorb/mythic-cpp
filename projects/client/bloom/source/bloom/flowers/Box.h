#pragma once

#include <bloom/layout/Measurement.h>
#include "Parent.h"

namespace bloom {

  namespace flowers {

    class BLOOM_EXPORT Box : public Parent {

        enum class Fit_To_Content {
            no,
            yes
        };
        Axis_Measurements measurement_bounds = {
          {{Measurements::stretch, 0}, {Measurements::stretch, 0}, {Measurements::stretch, 0}},
          {{Measurements::stretch, 0}, {Measurements::stretch, 0}, {Measurements::stretch, 0}},
        };

        Axis_Values absolute_bounds = {
          {0, 0},
          {0, 0}
        };

        Axis_Values relative_bounds = {
          {0, 0},
          {0, 0}
        };

        template<typename Axis>
        void fit_to_content(const Axis_Measurement &measurements, Axis_Value &relative_bounds,
                            const glm::vec2 &parent_dimensions, float content_length);

    protected:
        template<typename Axis>
        Fit_To_Content resolve_relative_bounds(const Axis_Measurement &measurements,
                                               const glm::vec2 &parent_dimensions,
                                               Axis_Value &relative_bounds);
    public:

        Box(Parent *parent) : Parent(parent) { }

        virtual ~Box() { }

        virtual const Axis_Values &get_absolute_bounds() {
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

        inline Parent_Dimensions get_dimensions() const {
          return {
            {absolute_bounds.x.far - absolute_bounds.x.near,
              measurement_bounds.x.length.get_type() == Measurements::stretch},
            {absolute_bounds.y.far - absolute_bounds.y.near,
              measurement_bounds.y.length.get_type() == Measurements::stretch},
          };
        }

        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_position) override;

        virtual bool get_relative_bounds(Axis_Values &result) override {
          result = relative_bounds;
          return true;
        }

    };

    glm::vec2 process_children(vector<unique_ptr<Flower>> &children, const glm::vec2& parent_dimensions);

    template<typename Axis>
    float resolve_measurement(const Measurement &measurement, const glm::vec2 &parent_dimensions) {
      switch (measurement.get_type()) {
        case Measurements::pixel:
          return measurement.get_value();

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