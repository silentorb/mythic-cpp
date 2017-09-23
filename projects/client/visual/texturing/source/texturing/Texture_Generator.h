#pragma once

#include <functional>

namespace texturing {

  typedef std::function<unsigned char *(int, int)> Texture_Generator;

  class Texture_Generator_Old {
  public:
      virtual unsigned char *generate(int &width, int &height) = 0;
  };

}



