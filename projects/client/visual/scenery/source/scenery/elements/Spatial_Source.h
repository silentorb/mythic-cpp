#pragma once

#include "commoner/dllexport.h"
#include <glm/mat4x4.hpp>

namespace scenery {

  class MYTHIC_EXPORT Spatial_Source {
  public:
      virtual glm::mat4 &get_absolute_orientation() = 0;
      virtual glm::mat4 &get_transform() = 0;
      virtual glm::mat4 &get_transform_without_scale() = 0;
  };
}