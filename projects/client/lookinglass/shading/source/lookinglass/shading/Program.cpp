#include "Program.h"
#include "lookinglass/glow.h"
#include <string>

namespace lookinglass {
  namespace shading {
    Program::Program(Shader first, Shader second) {
      id = glCreateProgram();
      glow::check_error("creating shader program");

      glAttachShader(id, first.id);
      glAttachShader(id, second.id);

      glLinkProgram(id);
      glow::check_error("linking cheater program");

      GLint result = 1;
      glGetProgramiv(id, GL_LINK_STATUS, &result);
      if (result != GL_TRUE) {
        GLint message_length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &message_length);
        GLchar *message = new GLchar[message_length + 1];
        glGetProgramInfoLog(id, 255, &message_length, message);
        throw std::string("Failed to compile shader code.  ") + message;
      }

      glValidateProgram(id);
      GLint validated = 1;
      glGetProgramiv(id, GL_VALIDATE_STATUS, &validated);
      if (validated == GL_FALSE)
        throw "Shader program unable to run in current state.";
    }

    Program::~Program() {
      glDeleteProgram(id);
    }

    void Program::activate() {
      glUseProgram(id);
      glow::check_error("set shader program");
    }
  }
}