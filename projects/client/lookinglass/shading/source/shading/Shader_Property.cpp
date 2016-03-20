#include "Shader_Property.h"
#include "lookinglass/glow.h"

namespace shading {

  Shader_Property::Shader_Property(const string &name, Program &program) :
    name(name) {
    uniform_index = glGetUniformLocation(program.get_id(), name.c_str());
  }

  void Shader_Property::set_matrix(const mat4 &value) {
    if (uniform_index != -1) {
      glUniformMatrix4fv(uniform_index, 1, GL_FALSE, (float *) &value);
    }
  }

  void Shader_Property::set_vec4(float x, float y, float z, float w) {
    if (uniform_index != -1) {
      glUniform4f(uniform_index, x, y, z, w);
    }
  }
}