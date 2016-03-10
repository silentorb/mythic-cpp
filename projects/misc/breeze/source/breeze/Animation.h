#pragma once

#include <promising/Promise.h>
#include "dllexport.h"
#include "Animation_Delegate.h"

namespace breeze {

  class MYTHIC_EXPORT Animation_Interface : no_copy {
  public:
      virtual ~Animation_Interface() { }

      virtual bool update(float delta) = 0;
  };

  template<typename T>
  class MYTHIC_EXPORT Animation : public Animation_Interface {
      float counter = 0;
      float duration;
      T start_value;
      T gap;
      T final_value;
      T &target;

      promising::Promise<void> &promise;

  public:
      Animation(float duration, T final_value, T &target,
                promising::Promise<void> &on_end) : duration(duration),
                                              final_value(final_value), target(target),
                                              promise(promise) {
        start_value = target;
        gap = final_value - start_value;
      }

  private:
      virtual ~Animation() override { }

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
  };
}