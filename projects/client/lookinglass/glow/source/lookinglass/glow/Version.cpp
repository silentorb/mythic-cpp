#include "Version.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  namespace glow {
    Version::Version() {
      auto text = glGetString(GL_VERSION);

    }

    Version::Version(int major, int minor) :
      major(major), minor(minor) {
      ES = false;
    }
  }
}