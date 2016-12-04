#include <bloom/Garden.h>
#include "Interactive.h"

using namespace glm;

namespace bloom {
  namespace flowers {

    Interactive::Interactive(Parent *parent)  {
      Parent_Implementation:: initialize_child(this, parent);
    }

    Interactive::~Interactive() {}


    glm::vec2 Interactive::update_dimensions(const vec2 &parent_dimensions) {
      return {parent_dimensions.x, parent_dimensions.y};
    }

    void Interactive::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {

    }

    void Interactive::update(float delta) {

    }

    void Interactive::render() {

    }


    bool Interactive::point_is_inside(const Flower *flower, const vec2 &point) {
      auto &bounds = flower->get_absolute_bounds();
      auto result = point.x > bounds.position.x
                    && point.y > bounds.position.y
                    && point.x < bounds.position.x + bounds.dimensions.x
                    && point.y < bounds.position.y + bounds.dimensions.y;

      return result;
    }
  }
}