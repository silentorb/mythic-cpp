#pragma once
#include "dllexport.h"
namespace lookinglass {
  namespace glow {

    class MYTHIC_EXPORT Version {
    public:
        int major;
        int minor;
        bool ES;

        Version();
        Version(int major, int minor);
    };
  }
}