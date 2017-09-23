#pragma once

#include "commoner/dllexport.h"
#include "Texture_Generator.h"
#include <string>

using namespace std;

namespace texturing {

  class MYTHIC_EXPORT Texture_From_File : public Texture_Generator_Old {
      string filename;

  public:

      Texture_From_File(const string &filename) : filename(filename) { }

      virtual unsigned char *generate(int &width, int &height) override;
  };
}