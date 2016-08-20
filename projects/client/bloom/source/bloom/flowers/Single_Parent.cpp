#include "Single_Parent.h"

namespace bloom {
  namespace flowers {
    void Single_Parent::add_child(Flower *child) {
      this->child = unique_ptr<Flower>(child);
      child->set_parent(this);
    }

    void Single_Parent::insert(Flower *child, int index) {
      add_child(child);
      child->set_parent(this);
    }

    void Single_Parent::remove_child(Flower *child) {
      if (this->child.get() == child)
        this->child.reset();
    }

    void Single_Parent::update(float delta) {
      if (child)
        child->update(delta);
    }

    void Single_Parent::render() {
      if (child)
        child->render();
    }

    bool Single_Parent::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      return child
             ? child->check_event(event_type, point)
             : false;
    }

    bool Single_Parent::affects_parent_dimensions() const {
      return child
             ? child->affects_parent_dimensions()
             : false;

    }
  }
}

