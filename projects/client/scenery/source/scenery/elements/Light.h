#pragma once

#include "dllexport.h"
#include "Element.h"

namespace scenery {

  struct Light_Data {
      int type;
      float brightness;
      vec3 position;
      vec3 direction;
      vec3 color;
  };

  class MYTHIC_EXPORT Light {
      Light_Data &data;

  public:
      Light(Light_Data &data) : data(data) { }
  };
}