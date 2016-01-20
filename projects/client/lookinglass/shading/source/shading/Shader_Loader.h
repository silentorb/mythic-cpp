#pragma once

#include "dllexport.h"

#include<string>

using namespace std;


namespace shading {

  class MYTHIC_EXPORT Shader_Loader {

  public:
      virtual string load(string source) = 0;
  };
}
