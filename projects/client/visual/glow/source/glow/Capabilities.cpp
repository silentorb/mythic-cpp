#include "Capabilities.h"
#include "glow.h"
#include "glow_gl.h"
#include <string>

namespace glow {

  static Capabilities *instance;

  Capabilities::Capabilities(Version version)
    : version(version) {
    extensions = glGetString(GL_EXTENSIONS);
    instance = this;

#ifdef glMultiDrawArrays
    _multidraw = glMultiDrawArrays != nullptr;
#else
    _multidraw = false;
#endif

    _uniform_layout = version.at_least(3, 0);
    _multisamplers = supports_extension("ARB_texture_multisample");
    _uniform_buffer = supports_extension("GL_ARB_uniform_buffer_object");
  }

  Capabilities::~Capabilities() {
    instance = nullptr;
  }

  bool Capabilities::supports_extension(const char *name) {
    return std::string(reinterpret_cast<const char *>(extensions)).find(name) != std::string::npos;
  }

  const Version &Capabilities::get_version() const {
    return version;
  }

  bool Capabilities::multidraw() const {
    return _multidraw;
  }

  bool Capabilities::uniform_layout() const {
    return _uniform_layout;
  }

  bool Capabilities::multisamplers() const {
    return _multisamplers;
  }

  Capabilities &Capabilities::get_instance() {
    return *instance;
  }

  bool Capabilities::uniform_buffer() const {
    return false;
  }
}
