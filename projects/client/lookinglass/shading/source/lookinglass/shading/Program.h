#pragma once

#include "dllexport.h"

#include "Shader.h"

namespace lookinglass {
  namespace shading {
    class MYTHIC_EXPORT Program {
        const unsigned int id;

    public:
        Program(Shader &first, Shader &second);
        ~Program();
        void activate();

        int get_id() const {
          return id;
        }
    };
  }
}