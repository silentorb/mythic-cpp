#pragma once

#include <promising/Promise.h>
#include "dllexport.h"
#include "Animation_Delegate.h"
#include "Animation.h"

namespace breeze {

  typedef std::function<bool(float)> Animation_Update;

  class MYTHIC_EXPORT Indefinite_Animation : public Animation {
      promising::Empty_Promise &promise;
      Animation_Update animation_update;

  public:
      Indefinite_Animation(Animation_Update animation_update)
        : animation_update(animation_update),
          promise(promising::Promise<void>::defer()) {

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