#include "Animation_Manager.h"

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
}