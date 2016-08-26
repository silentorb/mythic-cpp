#include "Shader_Property.h"
#include "lookinglass/glow.h"
#include "lookinglass/glow_gl.h"

namespace shading {

  Shader_Property::Shader_Property(const string &name, Program &program) :
    name(name) {
    uniform_index = glGetUniformLocation(program.get_id(), name.c_str());
  }

//  void Shader_Property::set_matrix(const mat4 &value) {
//    if (uniform_index != -1) {
//      glUniformMatrix4fv(uniform_index, 1, GL_FALSE, (float *) &value);
//    }
//  }
//
//  void Shader_Property::set_vec4(float x, float y, float z, float w) {
//    if (uniform_index != -1) {
//      glUniform4f(uniform_index, x, y, z, w);
//    }
//  }

  Matrix_Property::Matrix_Property(const string &name, Program *program) :
    property(Shader_Property(name, *program)) { }

  void Matrix_Property::set(const mat4 &value) {
    if (property.get_uniform_index() != -1) {
      glUniformMatrix4fv(property.get_uniform_index(), 1, GL_FALSE, (float *) &value);
    }
  }

  Vector4_Property::Vector4_Property(const string &name, Program &program) :
    property(Shader_Property(name, program)) { }

  void Vector4_Property::set(float x, float y, float z, float w) {
    if (property.get_uniform_index() != -1) {
      glUniform4f(property.get_uniform_index(), x, y, z, w);
    }
  }

  void Vector4_Property::set(glm::vec4 value) {
    if (property.get_uniform_index() != -1) {
      glUniform4f(property.get_uniform_index(), value.x, value.y, value.z, value.w);
    }
  }

  Float_Property::Float_Property(const string &name, Program &program) :
    property(Shader_Property(name, program)) { }

  Float_Property::Float_Property(const string &name, Program *program) :
    property(Shader_Property(name, *program)) { }

  void Float_Property::set(float value) {
    if (property.get_uniform_index() != -1) {
      glUniform1f(property.get_uniform_index(), value);
    }
  }
}