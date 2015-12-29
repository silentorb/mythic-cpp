#include "Shader_Manager.h"

namespace lookinglass {
  namespace shading {

    Shader_Manager::Shader_Manager(Shader_Loader *loader) :
      loader(loader) {

    }

    Shader *Shader_Manager::create_shader(Shader_Type type, const char *path) {
      string source;
      loader->load(path, source);
      auto code = process(type, source);
			return new Shader(type, code.c_str());
    }

    Program *Shader_Manager::create_program(Shader *vertex_shader, Shader *fragment_shader) {
			return nullptr;
    }

    string Shader_Manager::process(Shader_Type type, const string source) {
			return source;
    }

//    const Vertex_Schema &Shader_Manager::create_vertex_schema(const string name,
//                                                              std::initializer_list<Vertex_Attribute> attributes) {
//      auto schema = new Vertex_Schema(attributes);
//      vertex_schemas[name] = std::unique_ptr<Vertex_Schema>(schema);
//      return *schema;
//    }
  }
}