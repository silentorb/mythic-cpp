#pragma once
#include <functional>
#include <glm/vec2.hpp>

namespace texturing {
  class Texture;
}

namespace bloom {
  namespace flowers {

    // Position, Dimensions, Texture
    typedef std::function<void (glm::ivec2, glm::ivec2, texturing::Texture&)> Buffered_Flower_Renderer;
  }
}