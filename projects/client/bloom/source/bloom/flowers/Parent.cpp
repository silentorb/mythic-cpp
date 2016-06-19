#include "Parent.h"

namespace bloom {
  namespace flowers {

    void Parent::update(float delta) {
      for (auto &child : children) {
        child->update(delta);
      }
    }

    void Parent::render() {
      for (auto &child : children) {
        child->render();
      }
    }

    bool Parent::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      for (auto &child : children) {
        if (child->check_event(event_type, point))
          return true;
      }
      return false;
    }

  }
}