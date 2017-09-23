#pragma once

#include "commoner/dllexport.h"
#include "Mist.h"
#include "Doorway.h"
#include "Struct_Info.h"
#include <vector>
#include <memory>

using namespace shading;

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

      Program &get_program() const {
        return program;
      }
  };

  template<typename T>
  class MYTHIC_EXPORT Ancient_Mist : public Mist<T> {
      vector<unique_ptr<Ancient_Mist_Map>> maps;
      unique_ptr<Struct_Info> info;

//        Ancient_Mist(Ancient_Mist const &) = delete;
//        void operator=(Ancient_Mist const &) = delete;

  public:
      virtual ~Ancient_Mist() {}

      virtual void initialize(Struct_Info *info) override {
        this->info = unique_ptr<Struct_Info>(info);
      }

      virtual void add_program(Program &program) override {
        auto map = new Ancient_Mist_Map(program, *info);
        if (map->get_doorway_count() > 0)
          maps.push_back(unique_ptr<Ancient_Mist_Map>(map));
        else
          delete map;
      }

      virtual void remove_program(Program &program) override {
        for (int i = maps.size() - 1; i >= 0; --i) {
          if (&maps[i].get()->get_program() == &program) {
            maps.erase(maps.begin() + i);
          }
        }
      }

      virtual void update(T *data) override {
        for (auto &map : maps) {
          map->update(data);
        }
      }

      virtual void release() override {
        maps.clear();
      }
  };
}