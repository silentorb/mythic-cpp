#include "Child.h"
#include "Parent.h"

namespace bloom {
  namespace flowers {

    Child::Child(Parent *parent) {
      if (parent)
        parent->add_child(this);
    }


  }
}