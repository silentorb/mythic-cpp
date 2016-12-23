#pragma once

#include "commoner/dllexport.h"
#include "Timed_Animation.h"
//#include <iostream>

namespace breeze {

  class MYTHIC_EXPORT Delay : public Animation {
      float remainder;
      promising::Empty_Promise &promise;

  public:
      Delay(float duration, promising::Promise_Manager &promise_manager) :
        remainder(duration), promise(promising::Promise<void>::defer(promise_manager)) { }

      virtual bool update(float delta) override {
        remainder -= delta;
        if (remainder <= 0) {
          return true;
        }

        return false;
      }

      promising::Empty_Promise &get_promise() const {
        return promise;
      }

      virtual void on_finish() override {
        promise.resolve();
      }

      virtual void *get_target() const override {
        return nullptr;
      }
  };
}