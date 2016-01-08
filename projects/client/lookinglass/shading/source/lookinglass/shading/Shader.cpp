#include "Shader.h"
#include "lookinglass/glow.h"
#include <string>
#include <stdexcept>
#include "logger.h"

using namespace std;

namespace lookinglass {
  namespace shading {
    Shader::Shader(Shader_Type type, const char *code) :
      type(type), source_code(code) {
//      log_info("Creating shader: ") + code).c_str());
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
        log_info("Failed code: %s", code);
        throw std::runtime_error(std::string("Failed to compile shader code.  ") + message);
      }
    }

    Shader::~Shader() {
      glDeleteShader(id);
    }
  }
}
