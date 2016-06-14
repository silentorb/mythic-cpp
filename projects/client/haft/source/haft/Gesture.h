#pragma once
#include <glm/vec2.hpp>

namespace haft {

  enum class Gesture_Type {
      down,
      move,
      up
  };

  struct Gesture {
      Gesture_Type action;
      glm::ivec2 position;
  };
}