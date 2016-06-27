#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

namespace spatial {

  vec3 look_at_yaw_pitch(const vec3 &direction);
//  quat look_at_yaw_pitch(const vec3 &direction);
}