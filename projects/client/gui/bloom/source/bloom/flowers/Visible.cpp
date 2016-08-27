#include "Visible.h"

namespace bloom {
  namespace flowers {

    bool Visible::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      return visible
             ? Single_Parent::check_event(event_type, point)
             : false;
    }

    glm::vec2 Visible::update_dimensions(const glm::vec2 &parent_dimensions) {
      return child
             ? child->update_dimensions(parent_dimensions)
             : Common_Flower::update_dimensions(parent_dimensions);
    }

    void Visible::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      if (child)
        child->update_position(parent_position, parent_dimensions);
      else
        Common_Flower::update_position(parent_position, parent_dimensions);
    }

    void Visible::update(float delta) {
      Single_Parent::update(delta);
    }

    void Visible::render() {
      if (visible)
        Single_Parent::render();
    }
  }
}