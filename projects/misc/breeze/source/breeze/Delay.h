#pragma once

#include "dllexport.h"
#include "Animation.h"
//#include <iostream>

namespace breeze {

  class MYTHIC_EXPORT Delay : public Animation_Interface {
      float remainder;
      Empty_Promise &promise;

  public:
      Delay(float duration) : remainder(duration), promise(promising::Promise<void>::defer()) { }

      virtual bool update(float delta) override {
//        cout << remainder << " - " << delta << " = " << remainder - delta << endl;
        remainder -= delta;
        if (remainder <= 0) {
          promise.resolve();
          return true;
        }
//        else {
//          int k = 1;
//        }

        return false;
      }

      Empty_Promise &get_promise() const {
        return promise;
      }
  };
}