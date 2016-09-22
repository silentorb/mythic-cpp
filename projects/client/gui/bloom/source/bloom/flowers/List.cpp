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
    template<typename Axis>
    glm::vec2 List::update_dimensions_ascending(const glm::vec2 &parent_dimensions) {
      vec2 content_length;
      bool first = true;

      float resolved_spacing = resolve_measurement<Axis>(spacing, parent_dimensions);

      for (auto &child: children) {
        auto dimensions = parent_dimensions;
        if (Axis::get(dimensions) != 0)
          Axis::modify(dimensions, -Axis::get(content_length));

        auto child_bounds = child->update_dimensions(dimensions);

        if (Axis::other::get(content_length) < Axis::other::get(child_bounds))
          Axis::other::set(content_length, Axis::other::get(child_bounds));

        Axis::modify(content_length, Axis::get(child_bounds));
        if (!first)
          Axis::modify(content_length, resolved_spacing);

        first = false;
      }

      return content_length;
    }

    glm::vec2 List::update_dimensions(const glm::vec2 &parent_dimensions) {
      if (arrangement == Arrangement::down) {
        return update_dimensions_ascending<Vertical_Axis>(parent_dimensions);
      }
      else if (arrangement == Arrangement::right) {
        return update_dimensions_ascending<Horizontal_Axis>(parent_dimensions);
      }
      else {
        throw runtime_error("Not implemented");
      }
    }

//    glm::vec2 List::update_dimensions(const glm::vec2 &parent_dimensions) {
//      if (arrangement != Arrangement::down && arrangement != Arrangement::right)
//        throw runtime_error("Not implemented");
//
//      vec2 content_length;
//      bool first = true;
//
//      resolved_spacing = {0, 0};
//      if (arrangement == Arrangement::down) {
//        resolved_spacing.y = resolve_measurement<Vertical_Axis>(spacing, parent_dimensions);
//      }
//      else {
//        resolved_spacing.x = resolve_measurement<Horizontal_Axis>(spacing, parent_dimensions);
//      }
//
//      for (auto &child: children) {
//        auto dimensions = parent_dimensions;
//        if (arrangement == Arrangement::down) {
//          if (dimensions.y != 0)
//            dimensions.y -= content_length.y;
//        }
//        else {
//          if (dimensions.x != 0)
//            dimensions.x -= content_length.x;
//        }
//        auto child_bounds = child->update_dimensions(dimensions);
//
//        if (arrangement == Arrangement::down) {
//          if (content_length.x < child_bounds.x)
//            content_length.x = child_bounds.x;
//
//          content_length.y += child_bounds.y;
//          if (!first)
//            content_length.y += resolved_spacing.y;
//        }
//        else {
//          if (content_length.y < child_bounds.y)
//            content_length.y = child_bounds.y;
//
//          content_length.x += child_bounds.x;
//          if (!first)
//            content_length.x += resolved_spacing.x;
//        }
//
//        first = false;
//      }
//
//      return content_length;
//    }

    template<typename Axis>
    void List::update_position_ascending(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      auto position = parent_position;
      vec2 child_position;
      vec2 child_dimensions;
      float resolved_spacing = resolve_measurement<Axis>(spacing, parent_dimensions);

      for (auto &child : children) {
        // Restrict child bounds to normal size of the child so it does not try to center itself against
        // the size of the whole list.  (List children should be oblivous to the length of the list flower.)
        if (child->get_relative_bounds(child_position, child_dimensions)) {
          Axis::other::set(child_dimensions, Axis::other::get(parent_dimensions));
          child->update_position(position, child_dimensions);
        }
        else {
          child->update_position(position, parent_dimensions);
        }

        Axis::modify(position, Axis::get(child_position) + Axis::get(child_dimensions) + resolved_spacing);
      }
    }

    void List::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      if (arrangement == Arrangement::down) {
        return update_position_ascending<Vertical_Axis>(parent_position, parent_dimensions);
      }
      else if (arrangement == Arrangement::right) {
        return update_position_ascending<Horizontal_Axis>(parent_position, parent_dimensions);
      }
      else {
        throw runtime_error("Not implemented");
      }

//      auto position = parent_position;
//      vec2 child_position;
//      vec2 child_dimensions;
//      glm::vec2 resolved_spacing;
//      if (arrangement == Arrangement::down) {
//        resolved_spacing.y = resolve_measurement<Vertical_Axis>(spacing, parent_dimensions);
//      }
//      else {
//        resolved_spacing.x = resolve_measurement<Horizontal_Axis>(spacing, parent_dimensions);
//      }
//      for (auto &child : children) {
//        if (child->get_relative_bounds(child_position, child_dimensions)) {
//          // Restrict child bounds to normal size of the child so it does not try to center itself against
//          // the size of the whole list.  (List children should be oblivous to the length of the list flower.)
//          if (arrangement == Arrangement::down) {
//            child_dimensions.x = parent_dimensions.x;
//          }
//          else {
//            child_dimensions.y = parent_dimensions.y;
//          }
//          child->update_position(position, child_dimensions);
//        }
//        else {
//          child->update_position(position, parent_dimensions);
//        }
//
//        if (arrangement == Arrangement::down) {
//          position.y += child_position.y + child_dimensions.y + resolved_spacing.y;
//        }
//        else {
//          position.x += child_position.x + child_dimensions.x + resolved_spacing.x;
//        }
//      }
    }

//    const Axis_Values &List::get_absolute_bounds() const {
//      throw runtime_error("Not supported.");
//
//    }

  }
}