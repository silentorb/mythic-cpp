#pragma once

#include <glm/vec2.hpp>
#include "bloom/bloom_export.h"

namespace haft {
  class Input_State;
}

namespace bloom {

  struct Input_Result {
      bool mouse_click;
      bool dragging;
      bool start_down;
  };

  class BLOOM_EXPORT Garden_Input {
      glm::vec2 drag_start;
      glm::vec2 last_position;
      glm::vec2 position;
      bool dragging = false;
      bool is_down = false;
      void check_dragging(glm::vec2 position);

  public:
      Input_Result update_input(haft::Input_State &input_state);

      const glm::vec2 &get_drag_start() const {
        return drag_start;
      }

      const glm::vec2 &get_last_position() const {
        return last_position;
      }

      const glm::vec2 &get_position() const {
        return position;
      }

      bool is_dragging() const {
        return dragging;
      }
  };
}