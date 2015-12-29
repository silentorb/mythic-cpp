#pragma once
#include "dllexport.h"

#include<string>

using namespace std;

namespace lookinglass {
  namespace shading {

    class MYTHIC_EXPORT Shader_Loader {

    public:
        virtual void load(const char *source, string &result) = 0;
    };
  }
}
