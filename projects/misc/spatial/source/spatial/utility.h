#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "commoner/dllexport.h"

using namespace glm;

namespace spatial {

  MYTHIC_EXPORT vec3 look_at_yaw(const vec3 &direction);
  MYTHIC_EXPORT vec3 look_at_yaw(const vec3 &source, const vec3 &target);
  MYTHIC_EXPORT vec3 look_at_yaw_pitch(const vec3 &direction);
//  quat look_at_yaw_pitch(const vec3 &direction);
}