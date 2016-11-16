#pragma once

#include "Parent_Implementation.h"

namespace bloom {

  namespace flowers {

    enum class Arrangement {
        down,
        right,
        up,
        left,
    };

    class BLOOM_EXPORT List : public Parent_Implementation {
        Arrangement arrangement = Arrangement::down;
        Measurement spacing = {Measurements::pixel, 0};
//        glm::vec2 resolved_spacing;

        template<typename Axis>
        glm::vec2 update_dimensions_ascending(const glm::vec2 &parent_dimensions);

        template<typename Axis>
        void update_position_ascending(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions);

    public:
        List(Parent *parent = nullptr) : Parent_Implementation(parent) {}

        List(Arrangement arrangement, const Measurement spacing, Parent *parent = nullptr) :
          Parent_Implementation(parent), arrangement(arrangement), spacing(spacing) {}

        virtual ~List() override {}

        virtual const string get_class_name() const override {
          return "List";
        }

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
//        virtual const Axis_Values &get_absolute_bounds() const override;

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