#include "Animator.h"
#include "Delay.h"

namespace breeze {

  void Animator::update(float delta) {
    this->delta = delta;
    promise_manager.update();

    for (int i = animations.size() - 1; i >= 0; --i) {
//    for (auto &animation: animations) {
      auto animation = animations[i].get();
      if (animation->update(delta)) {
        animation->on_finish();
        animations.erase(animations.begin() + i);
      }
    }
  }

  promising::Promise<void> &Animator::delay(float duration) {
    auto animation = new Delay(duration, promise_manager);
    animations.push_back(unique_ptr<Animation>(animation));
    return animation->get_promise();
  }

  void Animator::add_animation(Animation *new_animation) {
    animations.push_back(unique_ptr<Animation>(new_animation));
  }

  void Animator::add_animation(Animation *new_animation, void *target) {
    if (target) {
      for (int i = 0; i < animations.size(); ++i) {
        auto &animation = animations[i];
        if (animation->get_target() == target) {
          animation->on_finish();
          animations.erase(animations.begin() + i);
          break;
        }
      }
    }

    add_animation(new_animation);
  }

  void Animator::clear() {
    animations.clear();
  }

}