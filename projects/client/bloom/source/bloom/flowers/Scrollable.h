#pragma once

#include <glm/vec2.hpp>
#include "Single_Parent.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Scrollable : public Single_Parent {
        glm::vec2 offset;
        glm::vec2 scroll_force;
        glm::vec2 velocity;
        bool allow_user_scrolling = true;
        float content_length;
        float boundary_length;

        void on_drag();

        void modify_inner();
        glm::ivec2 get_content_dimensions(const glm::vec2 &parent_dimensions);

    public:
        Scrollable();

        glm::vec2 &get_offset() {
          return offset;
        }

        void set_offset(const glm::vec2 &offset) {
          this->offset = offset;
        }

        void set_allow_user_scrolling(bool value) {
          allow_user_scrolling = value;
        }

        float get_range();
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;
        virtual void update(float delta) override;
    };
  }
}