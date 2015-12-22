#include "Shader.h"
#include "lookinglass/glow.h"
#include <string>

namespace lookinglass {
  namespace shading {
    Shader::Shader(Shader_Type type, const char *code) :
      type(type), source_code(code) {
      id = glCreateShader(type);
      glShaderSource(id, 1, &code, NULL);
      glow::check_error("Error loading shader code.");

      glCompileShader(id);
      GLint status = 1;
      glGetShaderiv(id, GL_COMPILE_STATUS, &status);
      if (status != GL_TRUE) {
        GLint message_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &message_length);
        GLchar *message = new GLchar[message_length + 1];
        glGetShaderInfoLog(id, 255, &message_length, message);
        throw std::string("Failed to compile shader code.  ") + message;
      }
    }

    Shader::~Shader(){
      glDeleteShader(id);
    }
  }
}
