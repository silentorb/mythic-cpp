#include "Ancient_Mist.h"
#include "lookinglass/glow.h"

namespace lookinglass {
  namespace through {

    Ancient_Mist_Map::Ancient_Mist_Map(Program &program, Struct_Info &info) : program(program) {

      int offset = 0;
      for (auto &field:info.get_fields()) {
        auto name = info.get_name() + "." + field->name;
        auto index = glGetUniformLocation(program.get_id(), name.c_str());
        if (index == -1)
          continue;

				doorways.push_back(unique_ptr<Doorway>(new Doorway(index, field->type, (Field_Type)offset)));
        offset += field->length;
      }
    }

    void Ancient_Mist_Map::update(void *data) {
      program.activate();
      for (auto &doorway : doorways) {
        doorway->update(data);
      }
    }
  }
}