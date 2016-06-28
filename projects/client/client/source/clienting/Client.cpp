#include "Client.h"
#include "lookinglass/House.h"
#include "haft/Input_Manager.h"
#include <audio/Player.h>

namespace clienting {

  Client::Client(House *house, audio::Speaker *speaker) :
    house(house),
    _is_closing(false),
    input_manager(new Input_Manager()),
    audio_player(new audio::Player(speaker)) {
  }

  Client::~Client() { }

  void Client::update() {
    house->update();
    input_manager->update();
  }

  bool Client::is_closing() {
    return _is_closing || house->is_closing();
  }

  Input_State &Client::get_current_input_state() const {
    return input_manager->get_current_state();
  }

  void Client::release() {
    house->release();
  }

  void Client::load() {
    house->load();
  }
}