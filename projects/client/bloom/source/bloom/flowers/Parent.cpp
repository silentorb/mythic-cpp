#include "Parent.h"

namespace bloom {
  namespace flowers {

    void Parent::update_layout() {
      for(auto &child : children) {
        child->render();
      }
    }

    void Parent::update(float delta) {
      for(auto &child : children) {
        child->render();
      }
    }

    void Parent::render() {
      for(auto &child : children) {
        child->render();
      }
    }

    Flower *Parent::get_parent() const {
      return parent;
    }

  }
}