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

  typedef function<void(sequencing::Conductor &, float, float)> Range_Handler;

  namespace performing {
    class Tempo_Loop {
        Loop loop;
        vector<Range_Handler> handlers;
        float beats;
        Range_Handler on_loop = nullptr;
        int skip = 0;
        double last_time = 0;
        bool started = false;

    public:

        Tempo_Loop(engineering::Engineer &engineer, float beats) : loop(engineer.get_sample_rate()), beats(beats) {}

//      Loop &get_loop() const {
//        return loop;
//      }

        void listen(Range_Handler handler) {
          handlers.push_back(handler);
        }

        void update(sequencing::Conductor &conductor);

        void trigger(sequencing::Conductor &conductor, double start, double end) {
          for (auto &handler: handlers) {
            handler(conductor, start, end);
          }
        }

        double get_position() const {
          return loop.get_position();
        }

        void set_position(double value) {
          loop.set_position(value);
        }

        const Range_Handler &get_on_loop() const {
          return on_loop;
        }

        void set_on_loop(const Range_Handler &on_loop) {
          Tempo_Loop::on_loop = on_loop;
        }

        float get_beats() const {
          return beats;
        }

        void clear_handlers() {
          handlers.clear();
        }
    };
  }
}