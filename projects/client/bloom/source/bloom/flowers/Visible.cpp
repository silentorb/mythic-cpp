#include "Visible.h"

namespace bloom {
  namespace flowers {
    bool Visible::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      return visible
             ? Parent::check_event(event_type, point)
             : false;
    }

    glm::vec2 Visible::update_dimensions(const glm::vec2 &parent_dimensions) {
      return children.size() > 0
             ? children[0]->update_dimensions(parent_dimensions)
             : Flower::update_dimensions(parent_dimensions);
    }

    void Visible::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      if (children.size() > 0)
        children[0]->update_position(parent_position, parent_dimensions);
      else
        Flower::update_position(parent_position, parent_dimensions);
    }

    void Visible::update(float delta) {
      Parent::update(delta);
    }

    void Visible::render() {
      if (visible)
        Parent::render();
    }
  }
}