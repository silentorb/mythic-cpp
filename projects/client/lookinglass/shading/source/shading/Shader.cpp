#include "Shader.h"
#include "lookinglass/glow.h"
#include <string>
#include <stdexcept>
#include "logger.h"

using namespace std;
using namespace lookinglass;

  namespace shading {
    Shader::Shader(Shader_Type type, string code) :
      type(type), source_code(code) {
//      log_info("Creating shader: ") + code).c_str());
      load();
    }

    Shader::~Shader() {
      free();
    }

    void Shader::free() {
      if (!id)
        return;

      glDeleteShader(id);
      id = 0;
    }

    void Shader::load() {
      id = glCreateShader(type);
      const char *code = source_code.c_str();
      glShaderSource(id, 1, &code, NULL);
      glow::check_error("Error loading shader code.");

      glCompileShader(id);
      GLint status = 1;
      glGetShaderiv(id, GL_COMPILE_STATUS, &status);
      if (status != GL_TRUE) {
        GLint message_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &message_length);
        GLchar *message = new GLchar[message_length + 1];
        glGetShaderInfoLog(id, 512, &message_length, message);
        log_info("Failed code: %s", source_code.c_str());
        throw std::runtime_error(std::string("Failed to compile shader code.  ") + message);
      }
    }
  }
