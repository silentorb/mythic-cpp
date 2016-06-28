#pragma once

#include "dllexport.h"

#include "Shader.h"
#include "resourceful/Resource.h"
#include "Vertex_Schema.h"
#include <vector>

namespace shading {

  class MYTHIC_EXPORT Program : public resourceful::Resource {
      unsigned int id;
      const string name;
      Shader &first, &second;
      vector<string> attribute_names;
      const Vertex_Schema *vertex_schema;

  public:
      Program(const string name, Shader &first, Shader &second, initializer_list<string> names);
      Program(const string &name, const string &first, const string &second, const Vertex_Schema &vertex_schema);
      ~Program();
      virtual void activate();

      int get_id() const {
        return id;
      }

      virtual void release() override;
      virtual void load() override;

      const string &get_name() const {
        return name;
      }

      void bind_attributes();

      const Vertex_Schema &get_vertex_schema() const {
        return *vertex_schema;
      }

      Shader &get_first() const {
        return first;
      }
  };

  class MYTHIC_EXPORT Program_Add_Listener {
  public:
      virtual void add_program(Program &program) = 0;
      virtual void remove_program(Program &program) = 0;
  };

}
