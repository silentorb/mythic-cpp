#include "Shader_Manager.h"
#include "Ancient_Code_Processor.h"
#include "lookinglass/glow/Capabilities.h"

namespace lookinglass {
  namespace shading {

    Shader_Manager::Shader_Manager(Shader_Loader *loader, glow::Capabilities &capabilities) :
      loader(loader), processor(create_processor(capabilities)) {

    }

    Code_Processor *Shader_Manager::create_processor(glow::Capabilities &capabilities) {
      if (capabilities.uniform_layout)
        return new Code_Processor(*loader);

      return new Ancient_Code_Processor(*loader);
    }

    Shader *Shader_Manager::create_shader(Shader_Type type, string path) {
      auto source =loader->load(path);
      auto code = process(type, source);
      return new Shader(type, code.c_str());
    }

    Program &Shader_Manager::create_program(string name, Shader &vertex_shader, Shader &fragment_shader) {
      auto program = new Program(vertex_shader, fragment_shader);
      programs[name] = program;
      return *program;
    }

//    const Vertex_Schema &Shader_Manager::create_vertex_schema(const string name,
//                                                              std::initializer_list<Vertex_Attribute> attributes) {
//      auto schema = new Vertex_Schema(attributes);
//      vertex_schemas[name] = std::unique_ptr<Vertex_Schema>(schema);
//      return *schema;
//    }
  }
}