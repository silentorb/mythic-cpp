#include "utility.h"
#include "glow.h"

namespace lookinglass {
  namespace glow {

    void check_error(const char *message){
      GLenum error = glGetError();

      if (error != GL_NO_ERROR)
        throw message;

    }
  }
}