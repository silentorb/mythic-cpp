#pragma once

#include "commoner/dllexport.h"
#include "Timed_Animation.h"
#include "Indefinite_Animation.h"
#include "3D_Animation.h"
#include <vector>
#include <memory>
#include <promising/Promise.h>

using namespace std;

namespace breeze {

  class MYTHIC_EXPORT Animation_Manager : no_copy {
      vector<unique_ptr<Animation>> animations;
      float delta;

      void add_animation(Animation *new_animation, void *target);

  public:
      void update(float delta);

      template<typename T>
      promising::Promise<void> &animate(T &target, const T final_value, float duration, Curve_Delegate curve) {
        auto animation = new Timed_Animation<T, Timed_Animation_Updater<T>>(target, final_value, duration, curve);
        add_animation(animation, &target);
        return animation->get_promise();
      }

      template<typename Accessor, typename Target, typename T>
      promising::Promise<void> &animate2(Target &target, const T final_value, float duration, Curve_Delegate curve) {
        auto animation = new Timed_Animation2<Accessor, Timed_Animation_Updater<T>, T, Target>(
          target, final_value, duration, curve);
        add_animation(animation, &target);
        return animation->get_promise();
      }

//      promising::Promise<void> &animate(Animation_Update animation_update) {
//        auto animation = new Indefinite_Animation(animation_update);
//        animations.push_back(unique_ptr<Animation>(animation));
//        return animation->get_promise();
//      }

//      promising::Promise<void> &animate_position_incremental(glm::vec3 &target, glm::vec3 final_value, float speed) {
//        auto animation = new Position_Animation_Incremental(target, final_value, speed);
//        animations.push_back(unique_ptr<Animation>(animation));
//        return animation->get_promise();
//      }

//      promising::Promise<void> &animate_position_over_time(glm::vec3 &target, glm::vec3 final_value,
//                                                           float speed, Curve_Delegate curve) {
//        auto animation = new Position_Animation_Over_Time(target, final_value, speed, curve);
//        animations.push_back(unique_ptr<Animation>(animation));
//        return animation->get_promise();
//      }

      promising::Promise<void> &slerp(glm::quat &target, glm::quat destination, float duration, Curve_Delegate curve) {
        auto animation = new Timed_Animation<glm::quat, Slerp_Updater>(target, destination, duration, curve);
        add_animation(animation, &target);
        return animation->get_promise();
      }


      promising::Promise<void> &delay(float duration);

      void clear();
  };
}