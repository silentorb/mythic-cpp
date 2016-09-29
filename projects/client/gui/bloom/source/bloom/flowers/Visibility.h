#pragma once

#include "Single_Parent.h"

namespace bloom {
  namespace flowers {
    class BLOOM_EXPORT Visibility : public Single_Parent {
        bool visible = true;

    public:
        virtual bool check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) override;

        Visibility() : Single_Parent() {}

        virtual ~Visibility() {}

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