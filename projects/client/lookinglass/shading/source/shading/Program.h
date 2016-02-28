#pragma once

#include "dllexport.h"

#include "Shader.h"
#include "resourceful/Resource.h"
#include <vector>

namespace shading {

  class MYTHIC_EXPORT Program : public resourceful::Resource {
      unsigned int id;
      const string name;
      Shader &first, &second;
      vector<string> attribute_names;

  public:
      Program(const string name,Shader &first, Shader &second, initializer_list<string> names);
      ~Program();
      void activate();

      int get_id() const {
        return id;
      }

      virtual void free() override;
      virtual void load() override;

      const string &get_name() const {
        return name;
      }

      void bind_attributes();
  };

  class MYTHIC_EXPORT Program_Add_Listener {
  public:
      virtual void add_program(Program &program) = 0;
  };

}
