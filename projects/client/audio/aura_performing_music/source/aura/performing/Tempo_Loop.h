#pragma once

#include <aura/processors/Loop.h>
#include <functional>
#include <vector>
#include <aura/engineering/Engineer.h>
#include <aura/sequencing/Beats.h>

using namespace std;

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  typedef function<void(sequencing::Conductor &, double, double)> Range_Handler;

  namespace performing {
    class Tempo_Loop {
        Loop loop;
        sequencing::Beats beats;
        Range_Handler on_loop = nullptr;
        double last_time = 0;

    public:

        Tempo_Loop(unsigned int sample_rate, float beats) : loop(sample_rate), beats(beats) {}

        void update(sequencing::Conductor &conductor);

        void set_on_loop(const Range_Handler &on_loop) {
          Tempo_Loop::on_loop = on_loop;
        }

        sequencing::Beats get_beats() const {
          return beats;
        }

        void set_beats(sequencing::Beats value){
          beats = value;
        }
    };
  }
}