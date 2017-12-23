#pragma once


#include "Version.h"

namespace glow {

  class Capabilities {
      const unsigned char *extensions;
      Version version;
      bool _multidraw;
      bool _uniform_layout;
      bool _multisamplers;
      bool _uniform_buffer;

      bool supports_extension(const char *name);

  public:
      Capabilities(Version version);

      virtual ~Capabilities();

      const Version &get_version() const;
      bool multidraw() const;
      bool uniform_layout() const;
      bool multisamplers() const;
      bool uniform_buffer() const;

      static Capabilities &get_instance();
  };
}

