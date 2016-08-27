#include "Garden_Input.h"
#include <haft/Input_State.h>
#include <iostream>
#include <glm/glm.hpp>

using namespace haft;

const float drag_minimum = 10;

namespace bloom {

  Input_Result Garden_Input::update_input(Input_State &input_state) {
    Input_Result result{
      false, false, false, false
    };
    last_position = position;

    for (auto &gesture : input_state.get_gestures()) {
      // Eventually position management will need to be more complicated to support multiple gestures.
      position = gesture.position;

      switch (gesture.action) {
        case Gesture_Type::down: {
//          std::cout << "down: " << to_string(gesture.position.x) << ", " << to_string(gesture.position.y) << std::endl;
          dragging = false;
          drag_start = gesture.position;
          is_down = true;
          result.down = true;
          break;
        }
        case Gesture_Type::move: {
//          std::cout << "move: " << to_string(gesture.position.x) << ", " << to_string(gesture.position.y) << endl;
          check_dragging(gesture.position);
          result.dragging = dragging;
          break;
        }
        case Gesture_Type::up: {
//          std::cout << "up:   " << to_string(gesture.position.x) << ", " << to_string(gesture.position.y) << endl;
          check_dragging(gesture.position);
          is_down = false;
          result.up = true;
          if (dragging) {
            dragging = false;
            result.dragging = true;
          }
          else {
            result.mouse_click = true;
          }
          break;
        }
      }
    }

    return result;
  }

  void Garden_Input::check_dragging(glm::vec2 position) {
    if (dragging || !is_down)
      return;

    float length = glm::distance(drag_start, position);
    if (length > drag_minimum) {
      dragging = true;
    }
  }


}