#include "Shader.h"
#include "lookinglass/glow.h"
#include <string>
#include <stdexcept>

#if __ANDROID__
#include <android/log.h>
#define log_info(...) ((void)__android_log_print(ANDROID_LOG_INFO, "mythic", __VA_ARGS__))
#endif

namespace lookinglass {
  namespace shading {
    Shader::Shader(Shader_Type type, const char *code) :
      type(type), source_code(code) {
#if __ANDROID__
      log_info("Creating shader: %s", code);
#endif
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
        throw std::runtime_error(std::string("Failed to compile shader code.  ") + message);
      }
    }

    Shader::~Shader() {
      glDeleteShader(id);
    }
  }
}
