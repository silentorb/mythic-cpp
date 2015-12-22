#pragma once

#include "Shader.h"
#include "Program.h"
#include "Shader_Loader.h"

namespace lookinglass {
  namespace shading {

    class Shader_Manager {
    private:
        Shader_Loader *loader;

    protected:
        virtual void process(Shader_Type type, const string source, string &result);

    public:
        Shader_Manager(Shader_Loader *loader);
        Shader *create_shader(Shader_Type type, const char *path);
        Program *create_program(Shader *vertex_shader, Shader *fragment_shader);
    };
  }
}