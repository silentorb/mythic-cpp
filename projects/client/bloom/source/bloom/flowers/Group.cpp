#include "Group.h"

using namespace glm;

glm::vec2 bloom::flowers::Group::update_dimensions(const glm::vec2 &parent_dimensions) {
  vec2 content_length;
  for (auto &child: children) {
    auto child_bounds = child->update_dimensions(parent_dimensions);
    if (child->affects_parent_dimensions()) {
      if (content_length.x < child_bounds.x)
        content_length.x = child_bounds.x;

      if (content_length.y < child_bounds.y)
        content_length.y = child_bounds.y;
    }
  }

  return content_length;
}

void bloom::flowers::Group::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
  for (auto &child: children) {
    child->update_position(parent_position, parent_dimensions);
  }
}
