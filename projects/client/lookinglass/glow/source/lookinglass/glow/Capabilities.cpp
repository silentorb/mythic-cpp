#include "Capabilities.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  namespace glow {

    Capabilities::Capabilities(Version version)
      : version(version) {

      multidraw = glMultiDrawArrays != nullptr;
      uniform_layout = version.major > 3;
    }

  }
}