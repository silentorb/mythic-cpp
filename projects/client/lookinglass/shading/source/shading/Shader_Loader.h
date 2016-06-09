#pragma once

#include "dllexport.h"
#include <functional>
#include <string>
#include "Shader_Type.h"

using namespace std;

namespace shading {

//  class MYTHIC_EXPORT Shader_Loader {
//  public:
//      virtual string load(const string source) = 0;
//  };

//  class MYTHIC_EXPORT Shader_Processor {
//  public:
//      virtual const string operator()(const string &source) = 0;
//  };
  typedef function<const string(Shader_Type, const string &)>  Shader_Processor;
}
