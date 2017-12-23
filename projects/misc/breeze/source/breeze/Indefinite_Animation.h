#pragma once

#include <promising/Promise.h>

#include "Animation_Delegate.h"
#include "Animation.h"

namespace breeze {

  typedef std::function<bool(float)> Animation_Update;

  class Indefinite_Animation : public Animation {
      promising::Empty_Promise &promise;
      Animation_Update animation_update;

  public:
      Indefinite_Animation(Animation_Update animation_update, promising::Promise_Manager &promise_manager)
        : animation_update(animation_update),
          promise(promising::Promise<void>::defer(promise_manager)) {

      }

      virtual ~Indefinite_Animation() override { }

      virtual bool update(float delta) override {
        if (animation_update(delta)) {
          promise.resolve();
          return true;
        }

        return false;
      }

      promising::Empty_Promise &get_promise() const {
        return promise;
      }
  };

}