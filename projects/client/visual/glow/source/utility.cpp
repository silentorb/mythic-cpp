#include <stdexcept>
#include "utility.h"
#include "glow.h"
#include <sstream>
#include "glow_gl.h"

namespace glow {

  string get_error_info(GLenum error) {
    switch (error) {
      case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";

      case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";

      case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    }

    std::ostringstream os;
    os << error;
    return os.str();
  }

#if COMMONER_DEBUG
  void check_error(const char *message) {
      static unsigned long step = 0;
      ++step;
      return;
      GLenum error = glGetError();

      if (error != GL_NO_ERROR) {
        auto text = "OpenGL Error: " + get_error_info(error) + string(message);
        throw std::runtime_error(text);
      }
    }
#endif
}
