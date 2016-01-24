#pragma once

#include "dllexport.h"

#include "Shader.h"
#include "resourceful/Resource.h"


namespace shading {

  class MYTHIC_EXPORT Program : public resourceful::Resource {
      unsigned int id;
      const string name;
      Shader &first, &second;

  public:
      Program(const string name,Shader &first, Shader &second);
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
  };

  class MYTHIC_EXPORT Program_Add_Listener {
  public:
      virtual void add_program(Program &program) = 0;
  };

}
