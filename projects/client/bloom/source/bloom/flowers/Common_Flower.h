#pragma once

#include "Flower.h"
#include "commoner/no_copy.h"
#include "Parent.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Common_Flower : no_copy, public virtual Flower {
    protected:
        Parent *parent;

    public:
        unsigned long debug_id = 0;

        virtual ~Common_Flower() {}

        virtual const Axis_Values &get_absolute_bounds() const override {
          return parent->get_absolute_bounds();
        }

        virtual Parent *get_parent() const override {
          return parent;
        }

        virtual void remove() override {
          parent->remove_child(this);
        }

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) {
          return parent_dimensions;
        }

        virtual bool affects_parent_dimensions() const override { return false; }

        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override {
          return false;
        }

        virtual bool get_relative_bounds(glm::vec2 &position, glm::vec2 &dimensions) override {
          return false;
        };

        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override {

        }

        virtual void update(float delta) override {

        }

        virtual void render() override {

        }

        virtual void set_parent(Parent *parent) override {
          this->parent = parent;
        }
    };

  }
}