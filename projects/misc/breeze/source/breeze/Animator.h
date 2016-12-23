#pragma once

#include "Timed_Animation.h"
#include "Indefinite_Animation.h"
#include "3D_Animation.h"
#include <vector>
#include <memory>
#include <promising/Promise.h>
#include <promising/Promise_Manager_Implementation.h>

using namespace std;

namespace breeze {

  class Animator : no_copy {
      vector<unique_ptr<Animation>> animations;
      float delta;
      promising::Promise_Manager_Implementation promise_manager;

      void add_animation(Animation *new_animation);
      void add_animation(Animation *new_animation, void *target);

  public:
      void update(float delta);

      template<typename T>
      promising::Promise<void> &animate(T &target, const T final_value, float duration, Curve_Delegate curve) {
        auto animation = new Timed_Animation<T, Timed_Animation_Updater<T>>(target, final_value, duration, curve,
                                                                            promise_manager);
        add_animation(animation, &target);
        return animation->get_promise();
      }

      template<typename Accessor, typename Target, typename T>
      promising::Promise<void> &animate2(Target &target, const T final_value, float duration, Curve_Delegate curve) {
        auto animation = new Timed_Animation2<Accessor, Timed_Animation_Updater<T>, T, Target>(target, final_value,
                                                                                               duration, curve,
                                                                                               promise_manager);
        add_animation(animation, &target);
        return animation->get_promise();
      }

      promising::Promise<void> &slerp(glm::quat &target, glm::quat destination, float duration, Curve_Delegate curve) {
        auto animation = new Timed_Animation<glm::quat, Slerp_Updater>(target, destination, duration, curve,
                                                                       promise_manager);
        add_animation(animation, &target);
        return animation->get_promise();
      }

      template<typename T>
      promising::Promise<void> &drive(const T start_value, const T final_value, float duration, Curve_Delegate curve,
                                      const Animation_Driver_Updater<T> &updater) {
        auto animation = new Animation_Driver<T>(start_value, final_value, duration, curve, updater, promise_manager);
        add_animation(animation);
        return animation->get_promise();
      }

      promising::Promise<void> &delay(float duration);

      void clear();
  };
}