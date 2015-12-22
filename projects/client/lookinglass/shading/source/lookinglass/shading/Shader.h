#pragma once

namespace lookinglass {
  namespace shading {

    enum Shader_Type {
        vertex = 0x8B31,
        fragment = 0x8B30
    };

    class Shader {
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