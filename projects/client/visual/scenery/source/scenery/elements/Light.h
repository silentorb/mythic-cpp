#pragma once


#include "Element.h"

namespace scenery {

  struct Light_Data {
      int type;
      float brightness;
      vec3 position;
      vec3 direction;
      vec3 color;
  };

  class Light {
      Light_Data &data;

  public:
      Light(Light_Data &data) : data(data) { }
  };
}