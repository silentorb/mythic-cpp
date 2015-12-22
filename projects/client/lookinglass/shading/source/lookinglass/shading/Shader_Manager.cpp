#include "Shader_Manager.h"

namespace lookinglass {
  namespace shading {

    Shader_Manager::Shader_Manager(Shader_Loader *loader) :
      loader(loader) {

    }

    Shader *Shader_Manager::create_shader(Shader_Type type, const char *path) {
      string source;
      loader->load(path, source);
      string code;
      process(type, source, code);
    }

    Program *Shader_Manager::create_program(Shader *vertex_shader, Shader *fragment_shader) {

    }

    void Shader_Manager::process(Shader_Type type, const string source, string & result){

    }
  }
}