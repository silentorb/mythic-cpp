#pragma once

#include "texturing/Texture_Generator.h"
#include <string>

using namespace std;

namespace svg {

  class Texture_From_SVG : public texturing::Texture_Generator_Old {
      string filename;

  public:

      Texture_From_SVG(const string &filename) : filename(filename) { }

      virtual unsigned char *generate(int &width, int &height) override;

  };
}