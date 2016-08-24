#include <bloom/layout/near_and_far.h>
#include "Box_Group.h"
#include "Group.h"
#include "bloom/layout/Axis.h"
#include "Parent_Implementation.h"

using namespace glm;

namespace bloom {
  namespace flowers {

    Box_Group::Box_Group(Parent *parent) {
      Parent_Implementation::initialize_child(this, parent);
      auto group = new Group();
      set_bottom(group);
      set_top(group);
    }

  }
}