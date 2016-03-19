#include "Capabilities.h"
#include "lookinglass/glow.h"
#include <memory>

namespace lookinglass {

  namespace glow {

    std::unique_ptr<Capabilities> capabilities;

    Capabilities::Capabilities(Version version)
      : version(version) {

#ifdef glMultiDrawArrays
      _multidraw = glMultiDrawArrays != nullptr;
#else
      multidraw = false;
#endif

      _multidraw = false; // For testing mobile code on desktop
      _uniform_layout = version.major > 3;
    }

    void Capabilities::initialize(Version version) {
      capabilities = unique_ptr<Capabilities>(new Capabilities(version));
    }

    Version& Capabilities::get_version() {
      return capabilities->version;
    }

    bool Capabilities::multidraw() {
      return capabilities->_multidraw;
    }

    bool Capabilities::uniform_layout() {
      return capabilities->_uniform_layout;
    }
  }
}