#include "Visibility.h"

namespace bloom {
  namespace flowers {

    bool Visibility::check_event(const Event &event) {
      return visible
             ? Single_Parent::check_event(event)
             : false;
    }

    glm::vec2 Visibility::update_dimensions(const glm::vec2 &parent_dimensions) {
      return child && visible
             ? child->update_dimensions(parent_dimensions)
             : Common_Flower::update_dimensions(parent_dimensions);
    }

    void Visibility::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      if (child && visible)
        child->update_position(parent_position, parent_dimensions);
      else
        Common_Flower::update_position(parent_position, parent_dimensions);
    }

    void Visibility::update(float delta) {
      Single_Parent::update(delta);
    }

    void Visibility::render() {
      if (visible)
        Single_Parent::render();
    }

  }
}