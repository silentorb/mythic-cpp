#include <iostream>
#include "Scrollable.h"
#include "bloom/garden/Garden_Input.h"
#include "bloom/Garden.h"

namespace bloom {

  Scrollable::Scrollable(Flower_Old *parent) : Flower_Old(parent) {
    listen(Events::drag, Flower_Delegate([this](Flower_Old *flower) {
      if (content_height <= axis_cache_inner.y.length)
        return;

      auto &input = garden.get_input();
      scroll_force.y += input.get_position().y - input.get_last_position().y;

//      std::cout << "content_height: " << to_string(content_height) << std::endl;
//      std::cout << "down: " << to_string(input.get_last_position().y) << ", " << to_string(input.get_position().y) <<
//      std::endl;

    }));

  }

  void Scrollable::modify_inner() {
    Flower_Old::modify_inner();

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

    auto range = content_height - axis_cache_inner.y.length;
    if (offset.y < 0 && offset.y < -range) {
      offset.y = -range;
      velocity.y = 0;
    }
    else if (offset.y > 0) {
      offset.y = 0;
      velocity.y = 0;
    }

    axis_cache_inner.x.near += offset.x;
    axis_cache_inner.y.near += offset.y;
  }

}