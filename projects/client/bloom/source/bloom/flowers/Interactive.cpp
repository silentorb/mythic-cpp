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

    Interactive::~Interactive() { }

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

    const Axis_Values &Interactive::get_absolute_bounds() {
      throw runtime_error("Not supported.");
    }

    bool Interactive::check_event(const songbird::Song<Flower_Delegate> &event_type, const glm::vec2 &point) {
      if (singer->has_listeners(event_type) && point_is_inside(point)) {
        singer->sing(event_type, this);
        return true;
      }

      return false;
    }

    bool Interactive::point_is_inside(const vec2 &point) {
//      auto &bounds = parent->get_absolute_bounds();
      vec2 corner_offset;

//      if (clip_bounds.get()) {
//        if (clip_bounds->y.absolute_far < bounds.get_corner().y)
//          corner_offset.y = clip_bounds->y.absolute_far - bounds.get_corner().y;
//      }
      auto &bounds = parent->get_absolute_bounds();
//      auto converter = Garden::get_instance().get_converter();
//      auto top_left = converter.convert_to_pixels({bounds.x.near, bounds.y.near});
//      auto bottom_right = converter.convert_to_pixels(vec2(bounds.x.far, bounds.y.far) + corner_offset);

      auto result = point.x > bounds.x.near
                    && point.y > bounds.y.near
                    && point.x < bounds.x.far
                    && point.y < bounds.y.far;

      return result;
    }
  }
}