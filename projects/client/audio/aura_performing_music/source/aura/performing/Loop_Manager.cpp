#include "Loop_Manager.h"

namespace aura {
  namespace performing {

    Tempo_Loop &Loop_Manager::get_loop_with_beat_count(float beats) {
      for (auto &loop:loops) {
        if (loop->get_beats() == beats)
          return *loop;
      }

      auto loop = new Tempo_Loop(engineer.get_sample_rate(), beats);
      loops.push_back(unique_ptr<Tempo_Loop>(loop));
      return *loop;
    }

    void Loop_Manager::update(sequencing::Conductor &conductor) {
      for (auto &loop: loops) {
        loop->update(conductor);
      }
    }

//    void Loop_Manager::clear() {
//      for (auto &loop : loops) {
//        loop->clear_handlers();
//      }
//    }
  }
}