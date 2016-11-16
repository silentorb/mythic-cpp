#include "Root.h"
#include "Common_Flower.h"

namespace bloom {
  namespace flowers {

    const Axis_Values &Root::get_absolute_bounds() const {
      return bounds;
    }

    glm::vec2 Root::update_dimensions(const glm::vec2 &parent_dimensions) {
      bounds.dimensions = parent_dimensions;
      return Group::update_dimensions(parent_dimensions);
    }
  }
}