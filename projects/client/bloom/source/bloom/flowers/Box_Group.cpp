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
      group = new Group();
      Single_Parent::add_child(group);

    }

    void Box_Group::add_child(Flower *child) {
      group->add_child(child);
    }

    void Box_Group::insert(Flower *child, int index) {
      group->insert(child, index);
    }

    void Box_Group::remove_child(Flower *child) {
      group->remove_child(child);
    }

    void Box_Group::update(float delta) {
      group->update(delta);
    }

    void Box_Group::render() {
      group->render();
    }

    bool Box_Group::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      return group->check_event(event_type, point);
    }

    void Box_Group::clear() {
      group->clear();
    }
  }
}