#pragma once

#include "dllexport.h"

#include "glm/glm.hpp"

using namespace glm;

namespace perspective {
  struct Viewport_Data {
      mat4 view;
      mat4 projection;;
      vec3 camera_direction;
  };
}
