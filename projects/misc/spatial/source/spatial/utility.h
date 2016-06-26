#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

namespace spatial {

  quat look_at_yaw_pitch(const vec3 &direction);
}