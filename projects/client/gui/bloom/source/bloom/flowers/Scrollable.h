#pragma once

#include <glm/vec2.hpp>
#include "Group.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Scrollable : public Group {
        enum class Direction {
            horizontal,
            vertical
        };

        enum class Mode {
            stationary,
            dragging,
            gliding,
            rebounding
        };
        glm::vec2 drag_start;
        glm::vec2 offset;
//        glm::vec2 scroll_force;
        glm::vec2 velocity;
        bool allow_user_scrolling = true;
        float content_length = 0;
        float boundary_length;
        Direction direction;
        Mode mode = Mode::stationary;

        void on_drag();
        void on_release();
        void update_glide(float delta);
        void update_rebound(float delta);
        glm::ivec2 get_content_dimensions(const glm::vec2 &parent_dimensions);
        void stop_velocity();

    public:
        Scrollable(Direction direction = Direction::vertical);

        virtual ~Scrollable() {}

        glm::vec2 &get_offset() {
          return offset;
        }

        void set_offset(const glm::vec2 &value);

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