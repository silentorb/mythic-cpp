#include "Scrollable.h"
#include "Interactive.h"
#include <songbird/Singer.h>
#include <bloom/Garden.h>

using namespace glm;

namespace bloom {
  namespace flowers {

    Scrollable::Scrollable(Direction direction) :
      direction(direction) {
      auto interactive = new Interactive(this);
      interactive->get_singer().listen(Events::drag, Flower_Delegate([this](Flower *flower) {
        on_drag();
      }));

      interactive->get_singer().listen(Events::mouse_down, Flower_Delegate([this](Flower *flower) {
        auto &input = Garden::get_instance().get_input();
        drag_start = input.get_position() - offset;
      }));

      interactive->get_singer().listen(Events::mouse_down, Flower_Delegate([this](Flower *flower) {
        on_release();
      }));
    }

    void Scrollable::on_drag() {
      if (!allow_user_scrolling)
        return;

      mode = Mode::dragging;
      auto &input = Garden::get_instance().get_input();
      velocity.y = input.get_position().y - input.get_last_position().y;
      set_offset(vec2(0, input.get_position().y - drag_start.y));
    }

    void Scrollable::set_offset(const glm::vec2 &value) {
      offset = value;
      auto range = get_range();
      float minimum = -range;
      float maximum = 0;
      const float margin = 25;

//      if (mode == Mode::dragging) {
      range += margin * 2;
      minimum -= margin;
      maximum += margin;
//      }

      if (offset.y < minimum) {
        offset.y = minimum;
        stop_velocity();
      }
      else if (offset.y > maximum) {
        offset.y = maximum;
        stop_velocity();
      }
    }

    void Scrollable::on_release() {
      auto range = get_range();
      if (offset.y >= -range && offset.y <= 0) {
        mode = Mode::gliding;
        return;
      }
      else {
        mode = Mode::rebounding;
      }
    }

    void Scrollable::stop_velocity() {
      velocity.y = 0;
      if (mode == Mode::gliding)
        mode = Mode::rebounding;
    }

    void Scrollable::update_glide(float delta) {
      auto reduction = velocity.y * 5.5f * delta;
      velocity.y -= reduction;
      if (glm::abs(velocity.y) < 0.1) {
        stop_velocity();
      }
      set_offset(offset + velocity);
    }

    void Scrollable::update_rebound(float delta) {
      auto range = get_range();
      const float rate = 7.0f;
      if (offset.y < -range) {
        auto distance = -offset.y - range;
        if (glm::abs(distance) < 0.1) {
          offset.y = -range;
          stop_velocity();
        }
        else {
          auto reduction = distance * rate * delta;
          offset.y += reduction;
        }
      }
      else if (offset.y > 0) {
        auto distance = offset.y;
        if (glm::abs(distance) < 0.1) {
          offset.y = 0;
          stop_velocity();
        }
        else {
          auto reduction = distance * rate * delta;
          offset.y -= reduction;
        }
      }
    }

    float Scrollable::get_range() {
      auto result = content_length - boundary_length;
      return result < 0
             ? 0
             : result;
    }

    glm::ivec2 Scrollable::get_content_dimensions(const glm::vec2 &parent_dimensions) {
      return ivec2(get_absolute_bounds().dimensions.x, content_length);
    }

    vec2 Scrollable::update_dimensions(const glm::vec2 &parent_dimensions) {
      bounds.dimensions = parent_dimensions;
      auto content_dimensions = Group::update_dimensions(ivec2(parent_dimensions.x, 0));
      content_length = direction == Direction::horizontal
                       ? content_dimensions.x
                       : content_dimensions.y;

      boundary_length = direction == Direction::horizontal
                        ? parent_dimensions.x
                        : parent_dimensions.y;

      return parent_dimensions;
    }

    void Scrollable::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      bounds.position = parent_position;
      auto position = parent_position + offset;
      Group::update_position(position, get_content_dimensions(parent_dimensions));
    }

    void Scrollable::update(float delta) {
      if (mode == Mode::gliding)
        update_glide(delta);
      else if (mode == Mode::rebounding)
        update_rebound(delta);

      Group::update(delta);
    }

    const Axis_Values &Scrollable::get_absolute_bounds() const {
      return bounds;
    }
  }
}