#include "Flower.h"

namespace bloom {
  namespace flowers {

    Flower::Flower(Flower *parent) {
      if (parent)
        parent->add_child(this);
    }

    void Flower::add_child(Flower *child) {
      child->parent = this;
      children.push_back(unique_ptr<Flower>(child));
    }

  }
}