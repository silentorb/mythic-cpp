#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

namespace spatial_old {

  vec3 look_at_yaw(const vec3 &direction);
  vec3 look_at_yaw(const vec3 &source, const vec3 &target);
  vec3 look_at_yaw_pitch(const vec3 &direction);
//  quat look_at_yaw_pitch(const vec3 &direction);
}