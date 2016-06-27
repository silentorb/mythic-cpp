#include "utility.h"
#include "angle.h"

namespace spatial {

//  quat look_at_yaw_pitch(const vec3 &direction) {
//    auto yaw = z_angle(direction.y, direction.x);
//    auto pitch = z_angle(direction.z, direction.y);
//    return quat(vec3(pitch, 0, yaw));
//  }

  vec3 look_at_yaw_pitch(const vec3 &direction) {
    auto yaw = z_angle(direction.y, direction.x);
    auto pitch = z_angle(direction.z, direction.y);
    return vec3(pitch, 0, yaw);
  }
}