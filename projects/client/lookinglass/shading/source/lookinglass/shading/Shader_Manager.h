#pragma once

#include "dllexport.h"
#include "Shader.h"
#include "Program.h"
#include "Shader_Loader.h"
#include <map>
#include <memory>
#include "Code_Processor.h"

namespace lookinglass {
  namespace glow {
    class Capabilities;
  }

  namespace shading {

    class MYTHIC_EXPORT Shader_Manager {
    private:
        unique_ptr<Shader_Loader> loader;
        unique_ptr<Code_Processor> processor;
        std::map<string, Program *> programs;

        Code_Processor *create_processor(glow::Capabilities &capabilities);

        string process(Shader_Type type, const string source) {
          return processor->process(type, source);
        }

    public:
        Shader_Manager(Shader_Loader *loader, glow::Capabilities &capabilities);
        Shader *create_shader(Shader_Type type, string path);
        Program &create_program(string name, Shader &vertex_shader, Shader &fragment_shader);

//        const Vertex_Schema &create_vertex_schema(const string name, std::initializer_list <Vertex_Attribute>attributes);
//
//        const Vertex_Schema &get_vertex_schema(const string name) {
//          return *vertex_schemas[name];
//        }


        const map<string, Program *> &get_programs() const {
          return programs;
        }
    };
  }
}