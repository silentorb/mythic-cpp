#include "Parent.h"

namespace bloom {
  namespace flowers {

//    void Parent::update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) {
//      for (auto &child : children) {
//        child->update_layout(parent_measurements, parent_bounds);
//      }
//    }

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

    void Parent::add_child(Child *child) {
      children.push_back(unique_ptr<Child>(child));
      child->parent = this;
    }

  }
}