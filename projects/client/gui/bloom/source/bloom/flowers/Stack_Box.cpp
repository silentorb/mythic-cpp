#include <bloom/layout/near_and_far.h>
#include "Stack_Box.h"
#include "bloom/layout/Axis.h"
#include "Parent_Implementation.h"

using namespace glm;

namespace bloom {
  namespace flowers {

//    Stack_Box::Stack_Box() {
//
//    }
//
//    Stack_Box::Stack_Box(Parent *first) {
//      set_bottom(first);
//    }

    void Stack_Box::set_stack_bottom(Parent *first) {
      Single_Parent::add_child(first);
    }

    void Stack_Box::set_stack_top(Parent *top) {
      this->top = top;
    }

    void Stack_Box::add_child(Flower *child) {
      top->add_child(child);
    }

    void Stack_Box::insert(Flower *child, int index) {
      top->insert(child, index);
    }

    void Stack_Box::remove_child(Flower *child) {
      top->remove_child(child);
    }

    void Stack_Box::clear() {
      top->clear();
    }

  }
}