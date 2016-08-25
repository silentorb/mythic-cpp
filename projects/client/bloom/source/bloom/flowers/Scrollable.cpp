#include "Scrollable.h"
#include "Interactive.h"
#include <songbird/Singer.h>
#include <bloom/Garden.h>

using namespace glm;

namespace bloom {
  namespace flowers {

    Scrollable::Scrollable() {
      auto interactive = new Interactive(this);
      interactive->get_singer().listen(Events::drag, Flower_Delegate([this](Flower *flower) {
        on_drag();
      }));
    }

    void Scrollable::on_drag() {
      if (!allow_user_scrolling || content_length <= boundary_length)
        return;

      auto &input = Garden::get_instance().get_input();
      scroll_force.y += input.get_position().y - input.get_last_position().y;

//      std::cout << "content_length: " << to_string(content_length) << std::endl;
//      std::cout << "down: " << to_string(input.get_last_position().y) << ", " << to_string(input.get_position().y) <<
//      std::endl;

    }


  void Scrollable::modify_inner() {

    if (scroll_force.y != 0) {
      if ((scroll_force.y < 0) == (velocity.y < 0)) {
        if (glm::abs(scroll_force.y) >= glm::abs(velocity.y))
          velocity.y = scroll_force.y;
//        else
//          velocity.y += scroll_force.y;
      }
      else {
        velocity.y = scroll_force.y;
      }
    }
    else if (velocity.y != 0) {
      velocity.y *= 0.7f;
      if (glm::abs(velocity.y) < 0.1) {
        velocity.y = 0;
      }
    }
    scroll_force = vec2();
    offset += velocity;

    auto range = get_range();
    if (offset.y < 0 && offset.y < -range) {
      offset.y = -range;
      velocity.y = 0;
    }
    else if (offset.y > 0) {
      offset.y = 0;
      velocity.y = 0;
    }
  }


    float Scrollable::get_range() {
      return content_length - boundary_length;
    }

    glm::ivec2 Scrollable::get_content_dimensions(const glm::vec2 &parent_dimensions) {
      return ivec2(get_absolute_bounds().dimensions.x, content_length);
    }

    vec2 Scrollable::update_dimensions(const glm::vec2 &parent_dimensions) {
      return Single_Parent::update_dimensions(ivec2(parent_dimensions.x, 0));
    }

    void Scrollable::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      Single_Parent::update_position(parent_position, get_content_dimensions(parent_dimensions));
    }

    void Scrollable::update(float delta) {
      modify_inner();
    }
  }
}