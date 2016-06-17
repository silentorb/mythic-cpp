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

    class BLOOM_EXPORT List : public Parent, public Child {
        Arrangement arrangement = Arrangement::down;
        Measurement spacing = {Measurements::pixel, 0};

    public:
        List(Parent *parent) : Child(parent) { }

        virtual ~List() override { }

        virtual glm::vec2 update_relative(const Parent_Dimensions &parent_dimensions) override;
        virtual void update_absolute(const glm::vec2 &parent_position) override;
        virtual const Axis_Values &get_absolute_bounds() override;

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