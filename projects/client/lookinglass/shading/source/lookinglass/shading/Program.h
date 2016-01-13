#pragma once

#include "dllexport.h"

#include "Shader.h"
#include "resourceful/Resource.h"

namespace lookinglass {
  namespace shading {

    class MYTHIC_EXPORT Program : public resourceful::Resource {
        unsigned int id;
        Shader &first, &second;

    public:
        Program(Shader &first, Shader &second);
        ~Program();
        void activate();

        int get_id() const {
          return id;
        }


        virtual void free() override;
        virtual void load() override;
    };

    class MYTHIC_EXPORT Program_Add_Listener {
    public:
        virtual void add_program(Program &program) = 0;
    };

  }
}