#pragma once

#include <functional>
#include <string>
#include "Shader_Type.h"

using namespace std;

namespace shading {

  typedef function<const string(Shader_Type, const string &)>  Shader_Processor;

}
