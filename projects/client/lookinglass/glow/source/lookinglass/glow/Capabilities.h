#pragma once

#include "lookinglass/glow/Version.h"

namespace lookinglass {
  namespace glow {

    class Capabilities {
    private:
        Version version;

    public:
        bool multidraw;
        bool uniform_layout;

        Capabilities(Version & version);
    };
  }
}

