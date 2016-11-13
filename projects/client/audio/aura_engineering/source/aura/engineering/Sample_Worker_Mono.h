#pragma once

#include <functional>
#include "Engineer.h"

namespace aura {
  namespace engineering {

//    using Sample_Worker_Delegate = std::function<void(float *, float, int &, float)>;

    template<typename T>
    class Sample_Worker_Mono {
        bool started = false;
        T& self;

    public:
        Sample_Worker_Mono(T *self) :
          self(*self) {}

        void update(float *buffer, int samples, Engineer &engineer) {
          float delta = 1.0f / engineer.get_sample_rate();
          int i = 0;
          if (!started) {
            started = true;
            float value = self.update_sample(0);
            for (int j = 0; j < engineer.get_channel_count(); ++j) {
              *buffer++ = value;
            }
            i = 1;
          }
          for (; i < samples; ++i) {
            float value = self.update_sample(delta);
            for (int j = 0; j < engineer.get_channel_count(); ++j) {
              *buffer++ = value;
            }
          }
        }

        void reset() {
          // May be able to squeak by without a mutex here.
          started = false;
        }
    };
  }
}