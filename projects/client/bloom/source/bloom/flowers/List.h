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
        glm::vec2 resolved_spacing;
        bool space_outside = false;

    public:
        List(Flower *parent) : Parent(parent) { }
        List(Arrangement arrangement, const Measurement spacing, Flower *parent) :
          Parent(parent), arrangement(arrangement), spacing(spacing) { }

        virtual ~List() override { }

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_position) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual const Axis_Values &get_absolute_bounds() const override;

        virtual bool affects_parent_dimensions() const override {
          return true;
        }

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

        bool get_space_outside() const {
          return space_outside;
        }

        void set_space_outside(bool space_outside) {
          List::space_outside = space_outside;
        }
    };
  }
}