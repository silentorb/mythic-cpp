#include "Shader_Manager.h"
#include "Ancient_Code_Processor.h"
#include "lookinglass/glow/Capabilities.h"
#include "resourceful/Resource_Manager.h"

using namespace resourceful;

namespace lookinglass {
  namespace shading {

    Shader_Manager::Shader_Manager(Shader_Loader *loader, glow::Capabilities &capabilities) :
      shaders(new Resource_Manager("shaders")),
      programs(new Resource_Manager("programs")),
      loader(loader),
      processor(create_processor(capabilities)) {

    }

    Shader_Manager::~Shader_Manager() { }

    Code_Processor *Shader_Manager::create_processor(glow::Capabilities &capabilities) {
      if (capabilities.uniform_layout)
        return new Code_Processor(*loader);

      return new Ancient_Code_Processor(*loader);
    }

    Shader &Shader_Manager::create_shader(Shader_Type type, string path) {
      auto source = loader->load(path);
      auto code = process(type, source);
      auto shader = new Shader(type, code.c_str());
      shaders->add_resource(shader);
      return *shader;
    }

    Program &Shader_Manager::create_program(string name, Shader &vertex_shader, Shader &fragment_shader) {
      auto program = new Program(vertex_shader, fragment_shader);
      programs->add_resource(program);
      for (auto& listener: program_added) {
        listener->add_program(*program);
      }
      return *program;
    }

//    const Vertex_Schema &Shader_Manager::create_vertex_schema(const string name,
//                                                              std::initializer_list<Vertex_Attribute> attributes) {
//      auto schema = new Vertex_Schema(attributes);
//      vertex_schemas[name] = std::unique_ptr<Vertex_Schema>(schema);
//      return *schema;
//    }

    void Shader_Manager::free() {
      shaders->free();
      programs->free();
    }

    void Shader_Manager::load() {
      shaders->load();
      programs->load();
      for (auto it = programs->begin(); it != programs->end(); ++it) {
        for (auto& listener : program_added) {
          auto program = (Program*)it->get();
          listener->add_program(*program);
        }
      }
    }
  }
}