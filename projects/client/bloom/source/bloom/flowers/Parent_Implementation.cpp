#include "Parent_Implementation.h"

namespace bloom {
  namespace flowers {

    void Parent_Implementation::update(float delta) {
      for (auto &child : children) {
        child->update(delta);
      }
    }

    void Parent_Implementation::render() {
      for (auto &child : children) {
        child->render();
      }
    }

    bool Parent_Implementation::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      for (auto &child : children) {
        if (child->check_event(event_type, point))
          return true;
      }
      return false;
    }

    void Parent_Implementation::add_child(Flower *child) {
      child->set_parent(this);
      children.push_back(unique_ptr<Flower>(child));
    }

    void Parent_Implementation::insert(Flower *child, int index) {
      child->set_parent(this);
      children.insert(children.begin() + index, unique_ptr<Flower>(child));
    }

    void Parent_Implementation::clear() {
      children.clear();
    }

    void Parent_Implementation::initialize_child(Flower *child, Parent *parent) {
      if (parent)
        parent->add_child(child);
    }

    void Parent_Implementation::remove_child(Flower *child) {
      for (int i = 0; i < children.size(); ++i) {
        if (children[i].get() == child) {
          children.erase(children.begin() + i);
          break;
        }
      }
    }
  }
}