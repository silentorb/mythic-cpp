#pragma once

#include "Parent.h"

namespace bloom {
  namespace flowers {

    enum class Arrangement {
        down,
        right,
        up,
        left,
    };

    class BLOOM_EXPORT List : public Parent {
        Arrangement arrangement = Arrangement::down;
        Measurement spacing = {Measurements::pixel, 0};

    public:
//        virtual void update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) override;

        virtual ~List() override { }

        Arrangement get_arrangement() const {
          return arrangement;
        }

        void set_arrangement(Arrangement arrangement) {
          List::arrangement = arrangement;
        }

        const Measurement &get_spacing() const {
          return spacing;
        }

        void set_spacing(const Measurement &spacing) {
          List::spacing = spacing;
        }
    };
  }
}