#include "Capabilities.h"
#include "lookinglass/glow.h"
#include <memory>

namespace glow {

  Capabilities *capabilities;

  Capabilities::Capabilities(Version version)
    : version(version) {
    capabilities = this;

#ifdef glMultiDrawArrays
    _multidraw = glMultiDrawArrays != nullptr;
#else
    _multidraw = false;
#endif

    _multidraw = false; // For testing mobile code on desktop
    _uniform_layout = version.major > 3;
  }

  Capabilities::~Capabilities() {
    capabilities = nullptr;
  }

  Version &Capabilities::get_version() {
    return capabilities->version;
  }

  bool Capabilities::multidraw() {
    return capabilities->_multidraw;
  }

  bool Capabilities::uniform_layout() {
    return capabilities->_uniform_layout;
  }
}
