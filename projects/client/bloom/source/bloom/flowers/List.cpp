#include <bloom/layout/Axis.h>
#include "List.h"
#include "Box.h"

using namespace glm;

namespace bloom {
  namespace flowers {

//    void List::update_layout(Axis_Measurements &parent_measurements, Axis_Values &parent_bounds) {
////      Parent::update_layout(parent_measurements, parent_bounds);
//      if (arrangement != Arrangement::down)
//        throw runtime_error("Not implemented");
//
//
//    }

    glm::vec2 List::update_dimensions(const glm::vec2 &parent_dimensions) {
      if (arrangement != Arrangement::down)
        throw runtime_error("Not implemented");

      vec2 content_length;
      bool first = true;
      resolved_spacing.y = resolve_measurement<Horizontal_Axis>(spacing, parent_dimensions);
      for (auto &child: children) {
        auto child_bounds = child->update_dimensions(parent_dimensions);
        if (content_length.x < child_bounds.x)
          content_length.x = child_bounds.x;

        content_length.y += child_bounds.y;
        if (!first)
          content_length.y += resolved_spacing.y;

        first = false;
      }

      return content_length;
    }

    void List::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      auto position = parent_position;
      Axis_Values child_bounds;

      for (auto &child : children) {
        child->update_position(position, parent_dimensions);
        if (child->get_relative_bounds(child_bounds)) {
          position.y += child_bounds.y.far + resolved_spacing.y;
        }
      }
    }

    const Axis_Values &List::get_absolute_bounds() {
      throw runtime_error("Not supported.");

    }

  }
}