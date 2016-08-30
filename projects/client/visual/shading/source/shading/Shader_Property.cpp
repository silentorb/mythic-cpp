#include "Shader_Property.h"
#include "glow.h"
#include "glow_gl.h"
#include <commoner/assert.h>

namespace shading {

  Shader_Property::Shader_Property(const string &name, Program &program) :
    name(name), program(program) {
    uniform_index = glGetUniformLocation((GLuint) program.get_id(), name.c_str());
//    Assert(uniform_index != -1);
    if (uniform_index == -1) {
      int k = 0;
    }
  }

  void Matrix_Property_Functions::update(unsigned int index, const mat4 &value) {
    glUniformMatrix4fv(index, 1, GL_FALSE, (float *) &value);
  }

  void Vector4_Property_Functions::update(unsigned int index, const vec4 &value) {
    glUniform4fv(index, 1, (float *) &value);
  }

  void Vector2_Property_Functions::update(unsigned int index, const vec2 &value) {
    glUniform2fv(index, 1, (float *) &value);
  }

  void Float_Property_Functions::update(unsigned int index, float value) {
    glUniform1f(index, value);
  }

}