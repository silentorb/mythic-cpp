#pragma once

#include "dllexport.h"

#include "lookinglass/glow/Version.h"

namespace glow {

  class MYTHIC_EXPORT Capabilities {
  private:
      Version version;
      Capabilities(Version version);
      bool _multidraw;
      bool _uniform_layout;

  public:

      static Version &get_version();

      static void initialize(Version version);
      static bool multidraw();
      static bool uniform_layout();
  };
}

