#include <songbird/Singer.h>
#include <bloom/Garden.h>
#include "Interactive.h"

using namespace glm;

namespace bloom {
  namespace flowers {

    Interactive::Interactive(Parent *parent) :
      Flower(parent),
      singer(new songbird::Singer()) {
    }

    Interactive::~Interactive() {}

    void Interactive::click(Flower_Delegate action) {
      singer->listen(Events::activate, action);
    }

    glm::vec2 Interactive::update_dimensions(const vec2 &parent_dimensions) {
      return {parent_dimensions.x, parent_dimensions.y};
    }

    void Interactive::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {

    }

    void Interactive::update(float delta) {

    }

    void Interactive::render() {

    }

    const Axis_Values &Interactive::get_absolute_bounds() const {
      throw runtime_error("Not supported.");
    }

    bool Interactive::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      if (singer->has_listeners(event_type) && point_is_inside(get_parent(), point)) {
        singer->sing(event_type, this);
        return true;
      }

      return false;
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