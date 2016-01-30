#pragma once

namespace texturing {

  class Texture_Generator {
  public:
      virtual unsigned char *generate(int &width, int &height) = 0;
  };

}



