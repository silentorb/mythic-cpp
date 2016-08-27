#pragma once

#include "commoner/dllexport.h"

#include "Version.h"

namespace glow {

  class MYTHIC_EXPORT Capabilities {
  private:
      Version version;
      bool _multidraw;
      bool _uniform_layout;

  public:
      Capabilities(Version version);

      virtual ~Capabilities();

      static Version &get_version();
      static bool multidraw();
      static bool uniform_layout();
  };
}

