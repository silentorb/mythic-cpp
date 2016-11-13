#pragma once

#include <functional>
#include "Engineer.h"

namespace aura {
  namespace engineering {

//    using Sample_Worker_Delegate = std::function<void(float *, float, int &, float)>;

    template<typename T>
    class Sample_Worker {
        bool started = false;
        T& self;

    public:
        Sample_Worker(T *self) :
          self(*self) {}

        void update(float *buffer, int length, Engineer &engineer) {
          float delta = 1.0f / engineer.get_sample_rate();
          auto samples = engineer.bytes_to_samples(length);
          int i = 0;
          if (!started) {
            started = true;
            self.update_sample(buffer, 0);
            buffer += engineer.get_channel_count();
            i = 1;
          }
          for (; i < samples; ++i) {
            self.update_sample(buffer, delta);
            buffer += engineer.get_channel_count();
          }
        }

        void reset() {
          // May be able to squeak by without a mutex here.
          started = false;
        }
    };
  }
}