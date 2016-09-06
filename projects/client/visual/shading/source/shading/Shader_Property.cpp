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

  void Matrix_Property_Functions::update(unsigned int index, const mat4 *values, int count) {
    glUniformMatrix4fv(index, count, GL_FALSE, (float *) values);
  }

  void Vector4_Property_Functions::update(unsigned int index, const vec4 *values, int count) {
    glUniform4fv(index, count, (float *) values);
  }

  void Vector2_Property_Functions::update(unsigned int index, const vec2 *values, int count) {
    glUniform2fv(index, count, (float *) values);
  }

  void Float_Property_Functions::update(unsigned int index, const float *values, int count) {
    glUniform1fv(index, count, values);
  }

}