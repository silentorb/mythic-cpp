#pragma once

#include <promising/Promise.h>
#include "dllexport.h"
#include "Animation_Delegate.h"
#include "Animation.h"
#include "curves.h"

using namespace promising;

namespace breeze {

  class MYTHIC_EXPORT Base_Timed_Animation : public Animation {
  protected:
      const float duration;
      const Curve_Delegate curve;
      float counter = 0;
      Empty_Promise &promise;

  public:
      Base_Timed_Animation(const float duration, const Curve_Delegate &curve) :
        duration(duration), curve(curve), promise(promising::Promise<void>::defer()) {}

      virtual ~Base_Timed_Animation() {}

      promising::Empty_Promise &get_promise() const {
        return promise;
      }

      virtual void on_finish() override {
        promise.resolve();
      }
  };

  template<typename T>
  struct Timed_Animation_Updater {
      static T get_value(T start_value, const T final_value, float counter) {
        T gap = final_value - start_value;
        return start_value + gap * counter;
      }
  };

  template<typename T, typename Updater>
  class MYTHIC_EXPORT Timed_Animation : public Base_Timed_Animation {
  protected:
      T start_value;
      const T final_value;
      T &target;

  public:
      Timed_Animation(T &target, const T final_value, float duration, Curve_Delegate curve)
        : Base_Timed_Animation(duration, curve), final_value(final_value), target(target) {
        start_value = target;
      }

      virtual ~Timed_Animation() override {}

      virtual bool update(float delta) override {

        counter += delta / duration;
        if (counter >= 1) {
          target = final_value;
          return true;
        }

        target = Updater::get_value(start_value, final_value, counter);
        return false;
      }

      virtual void *get_target() const override {
        return &target;
      }
  };

}