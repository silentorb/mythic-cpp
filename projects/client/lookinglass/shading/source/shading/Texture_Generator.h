#pragma once

namespace shading {

  class Texture_Generator {
  public:
      virtual void generate(float *data, int width, int height) = 0;
  };

}



