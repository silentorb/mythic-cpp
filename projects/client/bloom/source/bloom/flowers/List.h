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

    public:
        List(Parent *parent) : Parent(parent) { }
        List(Parent *parent, Arrangement arrangement, const Measurement spacing) :
          Parent(parent), arrangement(arrangement), spacing(spacing) { }

        virtual ~List() override { }

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_position) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual const Axis_Values &get_absolute_bounds() override;

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
    };
  }
}