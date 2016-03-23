#pragma once

#include "dllexport.h"
#include "Shader.h"
#include "Program.h"
#include "Shader_Loader.h"
#include <map>
#include <memory>
#include "Code_Processor.h"
#include "Vertex_Schema.h"
#include <vector>

namespace resourceful {
  class Resource_Manager;
}

namespace glow {
  class Capabilities;
}

namespace shading {

  class MYTHIC_EXPORT Shader_Manager {
  private:
      unique_ptr<Shader_Loader> loader;
      unique_ptr<Code_Processor> processor;
      unique_ptr<resourceful::Resource_Manager> shaders;
      unique_ptr<resourceful::Resource_Manager> programs;
      vector<Program_Add_Listener *> program_added;

      Code_Processor *create_processor();

      string process(Shader_Type type, const string source) {
        return processor->process(type, source);
      }


  public:
      Shader_Manager(Shader_Loader *loader);
      ~Shader_Manager();
      Shader &create_shader(Shader_Type type, string path);
      void register_program(Program *program);
      Program &create_program(string name, Shader &vertex_shader, Shader &fragment_shader,
                              initializer_list<string> names);
//      Program &create_program(string name, Shader &vertex_shader, Shader &fragment_shader,
//                              Vertex_Schema & vertex_schema);
      Program &create_program_from_files(const string name, const string vertex, const string fragment,
                                         initializer_list<string> names);

//      Program &create_program_from_files(const string name, const string vertex, const string fragment,
//                                         Vertex_Schema & vertex_schema);
//      template<typename T>
//      T &create_program_from_files(const string name, const string vertex, const string fragment,
//                                   Vertex_Schema & vertex_schema) {
//        auto program = new T(
//          name,
//          create_shader(Shader_Type::vertex, vertex),
//          create_shader(Shader_Type::fragment, fragment),
//          vertex_schema);
//
//        initialize_program(program);
//
//        return *program;
//      }

      void add_program_add_listener(Program_Add_Listener &listener) {
        program_added.push_back(&listener);
      }

      void free();
      void load();

      Program &get_program(const string name) const;
      Program *get_program_or_null(const string name) const;
      static Shader_Manager & get_instance();
  };
}
