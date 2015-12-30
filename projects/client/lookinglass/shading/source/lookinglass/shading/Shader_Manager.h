#pragma once

#include "dllexport.h"

#include "Shader.h"
#include "Program.h"
#include "Shader_Loader.h"
//#include "Vertex_Schema.h"
#include <map>
#include <memory>

namespace lookinglass {
  namespace shading {

    class MYTHIC_EXPORT Shader_Manager {
    private:
        unique_ptr<Shader_Loader> loader;
        std::map<string, Program *> programs;
//        std::map<string, std::unique_ptr<Vertex_Schema>> vertex_schemas;

    protected:
        virtual string process(Shader_Type type, const string source);

    public:
        Shader_Manager(Shader_Loader *loader);
        Shader *create_shader(Shader_Type type, const char *path);
        Program *create_program(Shader *vertex_shader, Shader *fragment_shader);

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