#include "Ancient_Mist.h"
#include "glow.h"
#include "logger.h"
#include "glow_gl.h"

namespace lookinglass {
  namespace through {

    Ancient_Mist_Map::Ancient_Mist_Map(Program &program, Struct_Info &info) : program(program) {
      log_info("creating mist map");
      int offset = 0;
      for (auto &field:info.get_fields()) {
        auto name = info.get_name() == "" ? field.name : info.get_name() + "." + field.name;
        auto index = glGetUniformLocation(program.get_id(), name.c_str());
        if (index == -1) {
          log_info("failed to find %s in %d", name.c_str(), program.get_id());
//          log_info("vertex code: %s", program.get_first().get_source_code().c_str());
          continue;
        }

        log_info("doorway %s", name.c_str());
        doorways.push_back(unique_ptr<Doorway>(new Doorway(index, field.type, (Field_Type) offset)));
        offset += field.length;

        glow::check_error("creating door");
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