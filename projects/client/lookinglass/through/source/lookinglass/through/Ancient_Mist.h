#pragma once

#include "dllexport.h"
#include "Mist.h"
#include "Doorway.h"
#include "Struct_Info.h"
#include <vector>
#include <memory>

namespace lookinglass {
  namespace through {

    class MYTHIC_EXPORT Ancient_Mist_Map {
        Program &program;
        vector<unique_ptr<Doorway>> doorways;

        Ancient_Mist_Map(Ancient_Mist_Map const &) = delete;
        void operator=(Ancient_Mist_Map const &) = delete;

    public:

        //			Ancient_Mist_Map(Program &program, Struct_Info &info);
        Ancient_Mist_Map(Program &program, Struct_Info &info);

        int get_doorway_count() {
          return doorways.size();
        }

        void update(void *data);
    };

    template<typename T>
    class MYTHIC_EXPORT Ancient_Mist : public Mist<T> {
        vector<unique_ptr<Ancient_Mist_Map>> maps;
        unique_ptr<Struct_Info> info;

//        Ancient_Mist(Ancient_Mist const &) = delete;
//        void operator=(Ancient_Mist const &) = delete;

    public:

        virtual void initialize(Struct_Info *info) {
          this->info = unique_ptr<Struct_Info>(info);
        }

        virtual void add_program(Program &program) {
          auto map = new Ancient_Mist_Map(program, *info);
          if (map->get_doorway_count() > 0)
            maps.push_back(unique_ptr<Ancient_Mist_Map>(map));
          else
            delete map;
        }

        virtual void update(T *data) {
          for (auto &map : maps) {
            map->update(data);
          }
        }

        virtual void free() override {
            maps.clear();
        }
    };
  }
}