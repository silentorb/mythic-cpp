#pragma once
#include "dllexport.h"

#include<string>

using namespace std;

namespace lookinglass {
  namespace shading {

    class MYTHIC_EXPORT Shader_Loader {

    public:
        virtual string load(string source) = 0;
    };
  }
}
