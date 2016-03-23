#pragma once

#include "dllexport.h"
#include "Program.h"
#include <string>
#include <glm/detail/type_mat.hpp>

using namespace std;
using namespace glm;

namespace shading {

  class MYTHIC_EXPORT Shader_Property {
      const string name;
      unsigned int uniform_index;

  public:
      Shader_Property(const string &name, Program &program);
//      void set_matrix(const mat4 &value);
//      void set_vec4(float x, float y, float z, float w);

      const unsigned int &get_uniform_index() const {
        return uniform_index;
      }
  };

  class MYTHIC_EXPORT Matrix_Property {
      Shader_Property property;
  public:
      Matrix_Property(const string &name, Program *program);
      void set(const mat4 &value);
  };

  class MYTHIC_EXPORT Vector4_Property {
      Shader_Property property;
  public:
      Vector4_Property(const string & name, Program & program);
      void set(float x, float y, float z, float w);
  };

  class MYTHIC_EXPORT Float_Property {
      Shader_Property property;
  public:
      Float_Property(const string & name, Program * program);
      void set(float value);
  };
}