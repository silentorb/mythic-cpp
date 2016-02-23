#include "Animation_Manager.h"

namespace breeze {

  void Animation_Manager::add_animation(Animation *animation) {
    animations.push_back(unique_ptr<Animation>(animation));
  }

  void Animation_Manager::update(float delta) {
    for (auto &animation: animations) {
      animation->update(delta);
    }
  }
}