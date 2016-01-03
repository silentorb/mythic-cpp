#include "Capabilities.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  namespace glow {

    Capabilities::Capabilities(Version version)
      : version(version) {

#ifdef glMultiDrawArrays
      multidraw = glMultiDrawArrays != nullptr;
#else
          multidraw = false;
#endif
      uniform_layout = version.major > 3;
    }

  }
}