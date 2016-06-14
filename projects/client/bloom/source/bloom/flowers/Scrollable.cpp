#include <iostream>
#include "Scrollable.h"
#include "bloom/garden/Garden_Input.h"
#include "bloom/Garden.h"

namespace bloom {

  Scrollable::Scrollable(Flower *parent) : Flower(parent) {
    listen(Events::drag, Flower_Delegate([this](Flower *flower) {
      if (content_height <= axis_cache_inner.y.length)
        return;

      auto &input = garden.get_input();
      offset.y += input.get_position().y - input.get_last_position().y;
//      std::cout << "offset: " << to_string(offset.y) << std::endl;
      std::cout << "down: " << to_string(input.get_last_position().y) << ", " << to_string(input.get_position().y) <<
      std::endl;

    }));

  }

  void Scrollable::modify_inner() {
    Flower::modify_inner();
    axis_cache_inner.x.near += offset.x;
    axis_cache_inner.y.near += offset.y;
  }

}