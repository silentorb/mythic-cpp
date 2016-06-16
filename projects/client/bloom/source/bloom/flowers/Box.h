#pragma once

#include <bloom/layout/Measurement.h>
#include "Parent.h"

namespace bloom {

  namespace flowers {

    class BLOOM_EXPORT Box : public Parent, public virtual Child {

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
        static float resolve_value(const Measurement &measurement, const Parent_Dimensions &parent_dimensions);

//        template<typename Axis, typename Side>
//        static float resolve_side_value(const Axis_Measurement &measurements, const Parent_Dimensions &parent_dimensions);

        template<typename Axis>
        static void resolve_relative_bounds(const Axis_Measurement &measurements,
                                            const Parent_Dimensions &parent_dimensions,
                                            Axis_Value &relative_bounds);

//        template <typename Axis>
//        void update_bounds(const Parent_Bounds &parent_bounds);

    public:
//        virtual void update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) override;

        Box(Parent *parent) : Child(parent) { }

        virtual void update_layout(const Parent_Dimensions &parent_bounds) override;
        virtual const Axis_Values &get_absolute_bounds() override;

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
            {absolute_bounds.x.near, absolute_bounds.x.far - absolute_bounds.x.near,
              measurement_bounds.x.length.get_type() == Measurements::stretch},
            {absolute_bounds.y.near, absolute_bounds.y.far - absolute_bounds.y.near,
              measurement_bounds.y.length.get_type() == Measurements::stretch},
          };
        }

        virtual ~Box() { }
    };
  }
}