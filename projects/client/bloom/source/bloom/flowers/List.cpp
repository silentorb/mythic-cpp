#include "List.h"
#include "Box.h"

namespace bloom {
  namespace flowers {

//    void List::update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) {
////      Parent::update_layout(parent_measurements, parent_bounds);
//      if (arrangement != Arrangement::down)
//        throw runtime_error("Not implemented");
//
//
//    }

    glm::vec2 List::update_relative(const Parent_Dimensions &parent_dimensions) {
      return process_children(children, parent_dimensions);
    }

    void List::update_absolute(const glm::vec2 &parent_position) {

    }

    const Axis_Values &List::get_absolute_bounds() {
      throw runtime_error("Not supported.");

    }

  }
}