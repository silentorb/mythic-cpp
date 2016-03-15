#pragma once

#include "dllexport.h"
#include "Animation.h"
#include <vector>
#include <memory>
#include <promising/Promise.h>

using namespace std;

namespace breeze {

  class MYTHIC_EXPORT Animation_Manager : no_copy {
      vector<unique_ptr<Animation_Interface>> animations;
      float delta;

  public:
      void update(float delta);

      template<typename T>
      promising::Promise<void> &animate(float duration, T &target, T final_value) {
        auto animation = new Animation<T>(duration, final_value, target);
        animations.push_back(unique_ptr<Animation_Interface>(animation));
        return animation->get_promise();
      }

      promising::Promise<void> &delay(float duration);

      void clear();
  };
}