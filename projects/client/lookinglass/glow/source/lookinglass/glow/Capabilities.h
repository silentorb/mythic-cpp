#pragma once
#include "dllexport.h"

#include "lookinglass/glow/Version.h"

namespace lookinglass {
  namespace glow {

    class MYTHIC_EXPORT Capabilities {
    private:
        Version version;

    public:
        bool multidraw;
        bool uniform_layout;

        Capabilities(Version version);
    };
  }
}

