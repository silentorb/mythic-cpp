#pragma once

#include<string>
#include "lookinglass/shading/Shader_Loader.h"

using namespace std;
using namespace lookinglass::shading;

namespace desktop {
  class Desktop_Shader_Loader : public Shader_Loader {

      virtual void load(const char *path, string &result);
  };

}
