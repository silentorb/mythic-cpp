#pragma once

#include <promising/Promise.h>
#include "dllexport.h"
#include "Animation_Delegate.h"
#include "Animation.h"

using namespace promising;

namespace breeze {

  template<typename T>
  class MYTHIC_EXPORT Timed_Animation : public Animation {
      float counter = 0;
      float duration;
      T start_value;
      T gap;
      T final_value;
      T &target;

      Empty_Promise &promise;

  public:
      Timed_Animation(float duration, T final_value, T &target)
        : duration(duration), final_value(final_value), target(target),
          promise(promising::Promise<void>::defer()) {

        start_value = target;
        gap = final_value - start_value;
      }

      virtual ~Timed_Animation() override { }

      virtual bool update(float delta) override {

        counter += delta;
        if (counter >= duration) {
          target = final_value;
          promise.resolve();
          return true;
        }

        target = start_value + gap * counter / duration;
        return false;
      }

      Empty_Promise &get_promise() const {
        return promise;
      }
  };

}