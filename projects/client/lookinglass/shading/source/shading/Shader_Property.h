#pragma once

#include "dllexport.h"
#include "Program.h"
#include <string>
#include <glm/detail/type_mat.hpp>

using namespace std;
using namespace glm;

namespace shading {

  class MYTHIC_EXPORT Shader_Property {
  protected:
      const string name;
      unsigned int uniform_index;

  public:
      Shader_Property(const string &name, Program &program);
      void set_matrix(const mat4 &value);
      void set_vec4(float x, float y, float z, float w);
  };

}