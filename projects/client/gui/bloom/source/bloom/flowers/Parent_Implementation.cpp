#include "Parent_Implementation.h"

namespace bloom {
  namespace flowers {

    Parent_Implementation::~Parent_Implementation() {

    }

    void Parent_Implementation::update(float delta) {
      // Incremented indexes may be slower than an iterator but is a simple way to deal with
      // at least some cases of children being removed during the update loop.
      for (int i = 0; i < children.size(); ++i) {
        children[i]->update(delta);
      }
    }

    void Parent_Implementation::render() {
      for (auto &child : children) {
        child->render();
      }
    }

    bool Parent_Implementation::check_event(const Event &event) {
      for (auto &child : children) {
        if (child->check_event(event))
          return true;
      }
      return false;
    }

    void Parent_Implementation::add_child(Flower *child) {
      if (child == this)
        throw runtime_error("Attempt to add parent to itself.");

      child->set_parent(this);
      children.push_back(unique_ptr<Flower>(child));
    }

    void Parent_Implementation::insert(Flower *child, int index) {
      if (child == this)
        throw runtime_error("Attempt to add parent to itself.");

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

    int Parent_Implementation::get_child_count() {
      return children.size();
    }

    Flower *Parent_Implementation::get_child(int index) {
      return children[index].get();
    }
  }
}
