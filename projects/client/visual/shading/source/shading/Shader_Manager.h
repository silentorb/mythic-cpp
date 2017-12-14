#pragma once

#include "commoner/dllexport.h"
#include "Shader.h"
#include "Program.h"
#include "Shader_Processor.h"
#include <map>
#include <memory>
#include "Code_Processor.h"
#include "Vertex_Schema.h"
#include <vector>
#include <resourceful/File_Loader.h>

namespace resourceful {
  class Resource_Manager;
}

namespace glow {
  class Capabilities;
}

namespace shading {

  class MYTHIC_EXPORT Shader_Manager {
  private:
      resourceful::File_Loader loader;
      Shader_Processor processor;
      unique_ptr<resourceful::Resource_Manager> shaders;
      unique_ptr<resourceful::Resource_Manager> programs;
      vector<Program_Add_Listener *> program_added;

      string process(Shader_Type type, const string &source) {
        return processor(type, source);
      }

  public:
      Shader_Manager(resourceful::File_Loader loader, Shader_Processor processor);
      ~Shader_Manager();
      Shader &create_shader_from_file(Shader_Type type, string path);
      Shader &create_shader(Shader_Type type, const string &source_code);
      void register_program(Program *program);
      Program &create_program(string name, Shader &vertex_shader, Shader &fragment_shader,
                              initializer_list<string> names);

      Program &create_program(string name, Shader &vertex_shader, Shader &fragment_shader,
                              const Vertex_Schema &vertex_schema);

      Program &create_program_from_files(const string name, const string vertex, const string fragment,
                                         initializer_list<string> names);

      Program &create_program_from_files(const string name, const string vertex, const string fragment,
                                         const Vertex_Schema &vertex_schema);

      void add_program_add_listener(Program_Add_Listener &listener) {
        program_added.push_back(&listener);
      }

      void release();
      void load();

      Program &get_program(const string name) const;
      Program *get_program_or_null(const string name) const;
      static Shader_Manager & get_instance();
      void remove_program(Program &program);
      void unregister_program(Program &program);
  };
}
