#pragma once
#include "dllexport.h"

#include "Shader.h"

namespace lookinglass {
  namespace shading {
    class MYTHIC_EXPORT Program {
    public:
        const unsigned int id;
        Program(Shader &first, Shader &second);
        ~Program();
        void activate();
    };
  }
}