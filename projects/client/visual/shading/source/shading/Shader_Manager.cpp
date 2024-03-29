#include "Shader_Manager.h"
#include "Ancient_Code_Processor.h"
#include "glow/Capabilities.h"
#include "resourceful/Resource_Manager.h"
#include <iostream>

using namespace resourceful;

namespace shading {

  Shader_Manager *instance = nullptr;

  Shader_Manager::Shader_Manager(File_Loader loader, Shader_Processor processor) :
    loader(loader),
    shaders(new Resource_Manager("shaders")),
    programs(new Resource_Manager("programs")),
    processor(processor) {
    instance = this;
  }

  Shader_Manager::~Shader_Manager() {
    // So children of this object do not unlisten to this after this is deleted. (Complications of destructor order).
    program_added.clear();
  }

  void Shader_Manager::register_program(Program *program) {
    for (auto &listener: program_added) {
      listener->add_program(*program);
    }
  }

  Shader &Shader_Manager::create_shader(Shader_Type type, const string &source_code) {
    auto shader = new Shader(type, source_code.c_str());
    shaders->add_resource(shader);
    return *shader;
  }

  Shader &Shader_Manager::create_shader_from_file(Shader_Type type, string path) {
    auto source = loader("shaders/" + path + ".glsl");
    auto code = process(type, source);
    auto shader = new Shader(type, code.c_str());
    shaders->add_resource(shader);
    return *shader;
  }

  Program &Shader_Manager::create_program(const string name, Shader &vertex_shader, Shader &fragment_shader,
                                          initializer_list<string> names) {
    auto program = new Program(name, vertex_shader, fragment_shader, names);
    programs->add_resource(program);
    register_program(program);
    return *program;
  }

  Program &Shader_Manager::create_program(string name, Shader &vertex_shader, Shader &fragment_shader,
                                          const Vertex_Schema &vertex_schema) {
    auto program = new Program(name, vertex_shader, fragment_shader, vertex_schema);
    programs->add_resource(program);
    register_program(program);
    std::cout << "Shader " << program->get_id() << ": " << name << std::endl;
    return *program;
  }

  Program &Shader_Manager::create_program_from_files(const string name, const string vertex, const string fragment,
                                                     initializer_list<string> names) {
    return create_program(
      name,
      create_shader_from_file(Shader_Type::vertex, vertex),
      create_shader_from_file(Shader_Type::fragment, fragment),
      names
    );
  }

  Program &Shader_Manager::create_program_from_files(const string name, const string vertex, const string fragment,
                                                     const Vertex_Schema &vertex_schema) {
    return create_program(
      name,
      create_shader_from_file(Shader_Type::vertex, vertex),
      create_shader_from_file(Shader_Type::fragment, fragment),
      vertex_schema
    );
  }

  void Shader_Manager::release() {
    shaders->release();
    programs->release();
  }

  void Shader_Manager::load() {
    shaders->load();
    programs->load();
    for (auto it = programs->begin(); it != programs->end(); ++it) {
      auto program = (Program *) it->get();
      for (auto &listener : program_added) {
        listener->add_program(*program);
      }
    }
  }

  Program &Shader_Manager::get_program(const string name) const {
    for (auto it = programs->begin(); it != programs->end(); ++it) {
      auto program = (Program *) it->get();
      if (program->get_name() == name)
        return *program;
    }

    throw runtime_error("Could not find shader program: " + name + ".");
  }

  Program *Shader_Manager::get_program_or_null(const string name) const {
    for (auto it = programs->begin(); it != programs->end(); ++it) {
      auto program = (Program *) it->get();
      if (program->get_name() == name)
        return program;
    }

    return nullptr;
  }

  Shader_Manager &Shader_Manager::get_instance() {
    return *instance;
  }

  void Shader_Manager::remove_program(Program &program) {
    unregister_program(program);

    programs->remove_resource(&program);
  }

  void Shader_Manager::unregister_program(Program &program) {
    for (auto &listener: program_added) {
      listener->remove_program(program);
    }

  }
}
