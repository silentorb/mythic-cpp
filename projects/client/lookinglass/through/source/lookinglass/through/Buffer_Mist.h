#pragma once

#include "Mist.h"
#include "Data_Buffer.h"
#include "Struct_Info.h"

namespace lookinglass {
  namespace through {

    template<typename T>
    class MYTHIC_EXPORT Buffer_Mist : public Mist<T> {
        Data_Buffer buffer;
    public:
        virtual void initialize(Struct_Info *info) override {
          buffer.initialize(info->get_id(), sizeof(T));
          delete info;
        }

        virtual void add_program(Program &program) override {

        }

        virtual void remove_program(Program &program) override {

        }

        virtual void update(T *data) override {
          buffer.update(data);
        }

        virtual void free() override {}
    };
  }
}