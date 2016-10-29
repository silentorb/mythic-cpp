#pragma once

#include <functional>
#include "Engineer.h"

namespace aura {
  namespace engineering {

//    using Sample_Worker_Delegate = std::function<void(float *, float, int &, float)>;

    template<typename T, typename Static_Class>
    class Sample_Worker {
        bool started = false;
        T& self;

    public:
        Sample_Worker(T *self) :
          self(*self) {}

        void update(float *buffer, int length, Engineer &engineer) {
          float delta = 1.0f / engineer.get_sample_rate();
          auto samples = engineer.bytes_to_samples(length);
          int index = 0;
          int i = 0;
          if (!started) {
            started = true;
            Static_Class::update_sample(self, buffer, 0, index);
            index += engineer.get_channel_count();
            i = 1;
          }
          for (; i < samples; ++i) {
            Static_Class::update_sample(self, buffer, delta, index);
            index += engineer.get_channel_count();
          }
        }
    };
  }
}