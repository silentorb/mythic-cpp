#pragma once

#include <aura/processors/Loop.h>
#include <functional>
#include <vector>
#include <aura/engineering/Engineer.h>

using namespace std;

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  typedef function<void(sequencing::Conductor &, double, double)> Range_Handler;

  namespace performing {
    class Tempo_Loop {
        Loop loop;
//        vector<Range_Handler> handlers;
        float beats;
        Range_Handler on_loop = nullptr;
        int skip = 100;
        double last_time = 0;

    public:

        Tempo_Loop(engineering::Engineer &engineer, float beats) : loop(engineer.get_sample_rate()), beats(beats) {}

//        void listen(Range_Handler handler) {
//          handlers.push_back(handler);
//        }

        void update(sequencing::Conductor &conductor);

//        void trigger(sequencing::Conductor &conductor, double start, double end) {
//          for (auto &handler: handlers) {
//            handler(conductor, start, end);
//          }
//        }

        void set_on_loop(const Range_Handler &on_loop) {
          Tempo_Loop::on_loop = on_loop;
        }

        float get_beats() const {
          return beats;
        }

//        void clear_handlers() {
//          handlers.clear();
//        }
    };
  }
}