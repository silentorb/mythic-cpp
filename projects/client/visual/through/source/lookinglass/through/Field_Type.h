#pragma once
#include "glm/glm.hpp"

namespace lookinglass {
  namespace through {

    enum Field_Type {
        matrix,
        vector3,
        integer,
        floating_point,
        structure,
        array
    };

    const int Field_Type_Lengths[] = {
      sizeof(glm::mat4),
      sizeof(glm::vec3),
      sizeof(int),
      sizeof(float),
      sizeof(void*),
      sizeof(void*)
    };
  }
}