#pragma once

#include "commoner/dllexport.h"
#include "Shader.h"
#include "resourceful/Resource.h"
#include "Vertex_Schema.h"
#include <vector>
#include <memory>

namespace shading {

  class Shader_Property;

  class MYTHIC_EXPORT Program : public resourceful::Resource, no_copy {
      unsigned int id;
      const std::string name;
      Shader &first, &second;
      vector<std::string> attribute_names;
      const Vertex_Schema *vertex_schema;
      std::vector<unique_ptr<Shader_Property>> properties;

      Shader_Property &add_property(Shader_Property *property);

  public:
      Program(const std::string name, Shader &first, Shader &second, initializer_list<std::string> names);
      Program(const std::string &name, Shader &first, Shader &second, const Vertex_Schema &vertex_schema);
      Program(const std::string &name, const std::string &first, const std::string &second,
              const Vertex_Schema &vertex_schema);
      ~Program();
      void activate();

      int get_id() const {
        return id;
      }

      virtual void release() override;
      virtual void load() override;

      const std::string &get_name() const {
        return name;
      }

      void bind_attributes();

      const Vertex_Schema &get_vertex_schema() const {
        return *vertex_schema;
      }

      Shader &get_first() const {
        return first;
      }

      Shader_Property *get_property(const std::string &name);

      template<typename T>
      T &create_property(const std::string &name) {
        auto property = get_property(name);
        if (property)
          static_cast<T &>(*property);

        return static_cast<T &>(add_property(new T(name, *this)));
      }

      bool is_active() const;
  };

  class MYTHIC_EXPORT Program_Add_Listener {
  public:
      virtual void add_program(Program &program) = 0;
      virtual void remove_program(Program &program) = 0;
  };

}
