#include "Client.h"
#include "lookinglass/House.h"
#include "haft/Input_Manager.h"

namespace clienting {

  Client::Client(House *house) :
    house(house),
    _is_closing(false),
    input_manager(new Input_Manager()) {
  }

  Client::~Client() { }


  void Client::update() {
    house->update();
    input_manager->update();
  }

  bool Client::is_closing() {
    return _is_closing || house->is_closing();
  }

}