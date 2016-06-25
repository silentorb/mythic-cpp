#pragma once

#include "dllexport.h"
#include "Timed_Animation.h"
#include "Indefinite_Animation.h"
#include "Incremental_Animation.h"
#include <vector>
#include <memory>
#include <promising/Promise.h>

using namespace std;

namespace breeze {

  class MYTHIC_EXPORT Animation_Manager : no_copy {
      vector<unique_ptr<Animation>> animations;
      float delta;

  public:
      void update(float delta);

      template<typename T>
      promising::Promise<void> &animate(float duration, T &target, T final_value) {
        auto animation = new Timed_Animation<T>(duration, final_value, target);
        animations.push_back(unique_ptr<Animation>(animation));
        return animation->get_promise();
      }

      promising::Promise<void> &animate(Animation_Update animation_update) {
        auto animation = new Indefinite_Animation(animation_update);
        animations.push_back(unique_ptr<Animation>(animation));
        return animation->get_promise();
      }

      promising::Promise<void> &animate_position(glm::vec3 &target, glm::vec3 final_value, float speed) {
        auto animation = new Position_Animation(target, final_value, speed);
        animations.push_back(unique_ptr<Animation>(animation));
        return animation->get_promise();
      }

//      template<typename T>
//      Animation<T> &animate(T &target, T final_value) {
//        auto animation = new Animation<T>(Animation::, final_value, target);
//        animations.push_back(unique_ptr<Animation_Interface>(animation));
//        return animation;
//      }

      promising::Promise<void> &delay(float duration);

      void clear();
  };
}