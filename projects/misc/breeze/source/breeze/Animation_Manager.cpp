#include "Animation_Manager.h"
#include "Delay.h"

namespace breeze {

  void Animation_Manager::update(float delta) {
    this->delta = delta;

    for (int i = animations.size() - 1; i >= 0; --i) {
//    for (auto &animation: animations) {
      auto animation = animations[i].get();
      if (animation->update(delta)) {
        animation->on_finish();
        animations.erase(animations.begin() + i);
      }
    }
  }

  promising::Promise<void> &Animation_Manager::delay(float duration) {
    auto animation = new Delay(duration);
    animations.push_back(unique_ptr<Animation>(animation));
    return animation->get_promise();
  }

  void Animation_Manager::add_animation(Animation *new_animation) {
    animations.push_back(unique_ptr<Animation>(new_animation));
  }

  void Animation_Manager::add_animation(Animation *new_animation, void *target) {
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

  void Animation_Manager::clear() {
    animations.clear();
  }

}