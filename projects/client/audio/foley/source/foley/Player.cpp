#include "Player.h"
#include <aura/engineering/Sample_Worker.h>

using namespace aura::engineering;

namespace foley {

  Player::Player(aura::engineering::Engineer &engineer) :
    engineer(engineer), sample_worker(new Sample_Worker<Player, Player>(this)) {}

  Player::~Player() {

  }

  void Player::update_sample(Player &self, float *buffer, float delta) {

  }

  void Player::update(float *buffer, int length) {
    sample_worker->update(buffer, length, engineer);
  }

//  void Player::add_sound(Sound *sound) {
//
//  }

  void Player::add_sound(unique_ptr<Sound> sound) {

  }
}