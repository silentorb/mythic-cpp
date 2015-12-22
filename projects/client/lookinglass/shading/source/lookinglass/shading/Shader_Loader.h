#pragma once

#include<string>

using namespace std;

namespace lookinglass {
  namespace shading {

    class Shader_Loader {

    public:
        virtual void load(const char *source, string &result) = 0;
    };
  }
}
