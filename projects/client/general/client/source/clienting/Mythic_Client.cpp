#include "Mythic_Client.h"
#include "lookinglass/House.h"
#include "haft/Input_Manager.h"
#include <audio/Player.h>

namespace clienting {

  Mythic_Client::Mythic_Client(House *house, audio::Speaker *speaker) :
    house(house),
    _is_closing(false),
    input_manager(new Input_Manager()),
    audio_player(new audio::Player(speaker)) {
  }

  Mythic_Client::~Mythic_Client() {}

  void Mythic_Client::render() {
    house->render();
  }

  void Mythic_Client::update_input() {
    input_manager->update();
  }

  bool Mythic_Client::is_closing() {
    return _is_closing || house->is_closing();
  }

  Input_State &Mythic_Client::get_current_input_state() const {
    return input_manager->get_current_state();
  }

  void Mythic_Client::release() {
    house->release();
  }

  void Mythic_Client::load() {
    house->load();
  }
}