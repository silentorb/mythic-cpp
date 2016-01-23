#pragma once

#include "dllexport.h"

#include "glm/glm.hpp"

using namespace glm;
namespace modeling {
  struct Textured_Vertex {
      vec3 position;
      vec3 normal;
      vec2 texture;
  };
}
