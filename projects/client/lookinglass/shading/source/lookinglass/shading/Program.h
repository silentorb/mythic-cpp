#pragma once

#include "Shader.h"

namespace lookinglass {
  namespace shading {
    class Program {
    public:
        unsigned int id;
        Program(Shader first, Shader second);
        ~Program();
        void activate();
    };
  }
}