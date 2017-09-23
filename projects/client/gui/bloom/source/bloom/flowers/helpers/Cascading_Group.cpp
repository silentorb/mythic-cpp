#include "Cascading_Group.h"

namespace bloom {
  namespace flowers {
    namespace helpers {
      glm::vec2 Cascading_Group::update_dimensions(const glm::vec2 &parent_dimensions) {
        glm::vec2 content_length = parent_dimensions;
        for (auto &child: children) {
          auto child_bounds = child->update_dimensions(content_length);
          if (child_bounds.y < 0)
            throw runtime_error("Dimensions cannot be negative");

          if (content_length.x < child_bounds.x)
            content_length.x = child_bounds.x;

          if (content_length.y < child_bounds.y)
            content_length.y = child_bounds.y;
        }

        return content_length;
      }
    }
  }
}