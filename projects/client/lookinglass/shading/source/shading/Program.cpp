#include "Program.h"
#include "lookinglass/glow.h"
#include <string>
#include <stdexcept>
#include "logger.h"

using namespace lookinglass;

namespace shading {
  Program::Program(const string name, Shader &first, Shader &second) :
    id(0), name(name), first(first), second(second) {
    load();
  }

  Program::~Program() {
    glDeleteProgram(id);
  }

  void Program::load() {
    if (id)
      return;

    id = glCreateProgram();
    glow::check_error("creating shader program");

    log_info("Program %d, Shaders: %d, %d", id, first.id, second.id);
    glAttachShader(id, first.id);
    glAttachShader(id, second.id);

    glLinkProgram(id);
    glow::check_error("linking shader program");

    GLint result = 1;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
      GLint message_length;
      glGetProgramiv(id, GL_INFO_LOG_LENGTH, &message_length);
      GLchar *message = new GLchar[message_length + 1];
      glGetProgramInfoLog(id, 255, &message_length, message);
      throw std::runtime_error(std::string("Failed to link shader code.  ") + message);
    }

    glValidateProgram(id);
    GLint validated = 1;
    glGetProgramiv(id, GL_VALIDATE_STATUS, &validated);
    if (validated == GL_FALSE)
      throw std::runtime_error("Shader program unable to run in current state.");
  }

  void Program::activate() {
    glUseProgram(id);
    glow::check_error("set shader program");
  }

  void Program::free() {
    if (!id)
      return;

    glDeleteProgram(id);
    id = 0;
  }
}
