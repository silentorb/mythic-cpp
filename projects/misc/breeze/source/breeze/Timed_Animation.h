#pragma once

#include <promising/Promise.h>
#include "Animation_Delegate.h"
#include "Animation.h"
#include "curves.h"

namespace breeze {

  class  Base_Timed_Animation : public Animation {
  protected:
      const float duration;
      const Curve_Delegate curve;
      float counter = 0;
      promising::Empty_Promise &promise;

  public:
      Base_Timed_Animation(const float duration, const Curve_Delegate &curve,
                                 promising::Promise_Manager &promise_manager) :
        duration(duration), curve(curve), promise(promising::Promise<void>::defer(promise_manager)) {}

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
  class Timed_Animation : public Base_Timed_Animation {
  protected:
      T start_value;
      const T final_value;
      T &target;

  public:
      Timed_Animation(T &target, const T final_value, float duration, Curve_Delegate curve,
                            promising::Promise_Manager &promise_manager)
        : Base_Timed_Animation(duration, curve, promise_manager), final_value(final_value), target(target) {
        start_value = target;
      }

      virtual ~Timed_Animation() override {}

      virtual bool update(float delta) override {

        counter += delta / duration;
        if (counter >= 1) {
          target = final_value;
          return true;
        }

        target = Updater::get_value(start_value, final_value, curve(counter));
        return false;
      }

      virtual void *get_target() const override {
        return &target;
      }
  };

  template<typename Accessor, typename Updater, typename T, typename Target>
  class Timed_Animation2 : public Base_Timed_Animation {
  protected:
      T start_value;
      const T final_value;
      Target &target;

  public:
      Timed_Animation2(Target &target, const T final_value, float duration, Curve_Delegate curve,
                             promising::Promise_Manager &promise_manager)
        : Base_Timed_Animation(duration, curve, promise_manager), final_value(final_value), target(target) {
        start_value = Accessor::get(target);
      }

      virtual ~Timed_Animation2() override {}

      virtual bool update(float delta) override {

        counter += delta / duration;
        if (counter >= 1) {
          Accessor::set(target, final_value);
          return true;
        }

        Accessor::set(target, Updater::get_value(start_value, final_value, curve(counter)));
        return false;
      }

      virtual void *get_target() const override {
        return &target;
      }
  };

  template<typename T>
  using Animation_Driver_Updater = std::function<void(T)>;

  template<typename T>
  class Animation_Driver : public Base_Timed_Animation {
  protected:
      const T start_value;
      const T final_value;
      const Animation_Driver_Updater<T> updater;
      T range;

  public:

      Animation_Driver(const T start_value, const T final_value, float duration, Curve_Delegate curve,
                             const Animation_Driver_Updater <T> &updater,
                             promising::Promise_Manager &promise_manager)
        : Base_Timed_Animation(duration, curve, promise_manager),
          start_value(start_value), final_value(final_value), updater(updater) {
        range = final_value - start_value;
      }

      virtual ~Animation_Driver() override {}

      virtual bool update(float delta) override {

        counter += delta / duration;
        if (counter >= 1) {
          updater(final_value);
          return true;
        }

        updater(start_value + curve(counter) * range);
        return false;
      }

      void *get_target() const override {
        return nullptr;
      }
  };

}