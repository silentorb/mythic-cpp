#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace spatial_old {

  using vec3 = glm::vec3;
  using quat = glm::quat;
  using mat4 = glm::mat4;

  struct Position {
      vec3 translation;
      quat orientation;
  };

  struct Translation : public Position {
      vec3 scale;
  };

//  class Spatial_Body {
//  public:
//      virtual Position get_position() = 0;
//      virtual const Position get_position() const = 0;
//
//      virtual const Translation get_translation() const = 0;
//      virtual Translation get_translation() = 0;
//  };
}
