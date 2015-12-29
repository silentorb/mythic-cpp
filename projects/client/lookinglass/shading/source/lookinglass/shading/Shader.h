#pragma once
#include "dllexport.h"

namespace lookinglass {
  namespace shading {

    enum Shader_Type {
        vertex = 0x8B31,
        fragment = 0x8B30
    };

    class MYTHIC_EXPORT Shader {
    private:
        Shader_Type type;
        const char *source_code;

    public:
        unsigned int id;
        Shader(Shader_Type type, const char *code);
        ~Shader();
    };
  }
}