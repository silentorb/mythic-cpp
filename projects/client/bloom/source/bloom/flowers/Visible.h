#pragma once

#include "Parent.h"

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Visible : public Parent {
        bool visible = true;

    public:
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;

        Visible(Flower *parent) : Parent(parent) {}

        virtual void update(float delta) override;
        virtual void render() override;

        bool is_visible() const {
          return visible;
        }

        void set_visible(bool value) {
          visible = value;
        }

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
    };

  }
}