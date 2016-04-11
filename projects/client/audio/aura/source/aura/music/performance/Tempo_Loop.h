#pragma once

#include <aura/processors/Loop.h>
#include "dllexport.h"
#include <functional>
#include <vector>

using namespace std;

namespace aura {
  class Conductor;

  typedef function<void(Conductor &, float, float)> Range_Handler;

  class MYTHIC_EXPORT Tempo_Loop {
      Loop loop;
      vector<Range_Handler> handlers;
      float beats;

  public:

      Tempo_Loop(Engineer &engineer, float beats) : loop(engineer), beats(beats) { }

//      Loop &get_loop() const {
//        return loop;
//      }

      void listen(Range_Handler handler) {
        handlers.push_back(handler);
      }

      void update(Conductor &conductor);

      double get_position() const {
        return loop.get_position();
      }

      void set_position(double value) {
        loop.set_position(value);
      }

  };
}