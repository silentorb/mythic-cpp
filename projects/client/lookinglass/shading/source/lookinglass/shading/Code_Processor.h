#pragma once

#include "Shader.h"
#include "Shader_Loader.h"

namespace lookinglass {
  namespace shading {

    class Code_Processor {
    private:
        Shader_Loader& shader_loader;
    protected:
        string process_includes(Shader_Type type, const string source);
    public:

        Code_Processor(Shader_Loader & shader_loader);

        virtual string process(Shader_Type type, const string source);
    };
  }
}