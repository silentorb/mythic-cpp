#include <stdexcept>
#include "utility.h"
#include "glow.h"
#include <sstream>

namespace lookinglass {
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

      std::ostringstream os ;
      os << error ;
      return os.str() ;
    }

    void check_error(const char *message) {
      GLenum error = glGetError();

      if (error != GL_NO_ERROR)
        throw std::runtime_error("OpenGL Error: " + get_error_info(error) + string(message));
    }
  }
}