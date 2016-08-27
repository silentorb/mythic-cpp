#include "Simple_Element.h"

namespace scenery {

  void Simple_Element::set_parent(Parent *new_parent, bool update_others) {
    if (parent == new_parent)
      return;

    if (!update_others) {
      parent = new_parent;
      return;
    }

    if (parent && new_parent) {
      this->parent->move_child(*this, *new_parent);
    }
    else if (new_parent) {
      parent = new_parent;
      parent->add_child(*this);
    }
    else {
      remove();
    }
  }
}