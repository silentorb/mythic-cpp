#include "Animation_Manager.h"
#include "Delay.h"

namespace breeze {

  void Animation_Manager::update(float delta) {
    this->delta = delta;

    for (int i = animations.size() - 1; i >= 0; --i) {
//    for (auto &animation: animations) {
      auto animation = animations[i].get();
      if (animation->update(delta)) {
        animations.erase(animations.begin() + i);
      }
    }
  }

  promising::Promise<void> &Animation_Manager::delay(float duration) {
    auto animation = new Delay(duration);
    animations.push_back(unique_ptr<Animation_Interface>(animation));
    return animation->get_promise();
  }

  void Animation_Manager::clear() {
    animations.clear();
  }
}