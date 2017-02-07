#pragma once

#include "Tempo_Loop.h"

namespace aura {
  namespace performing {

    class Loop_Manager {
        vector<unique_ptr<Tempo_Loop>> loops;
        engineering::Engineer &engineer;

    public:
        Loop_Manager(engineering::Engineer &engineer) : engineer(engineer) {}
        Tempo_Loop &get_loop_with_beat_count(float beats);
        void update(sequencing::Conductor &conductor);
        void clear();
    };
  }
}