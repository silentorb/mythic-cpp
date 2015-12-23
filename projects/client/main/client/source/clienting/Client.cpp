#include "Client.h"
#include "lookinglass/House.h"

namespace clienting {

  Client::Client(House &house) :
    house(house) {

  }

  void Client::update() {
    house.start_update();
    house.finish_update();
  }

  bool Client::is_closing() {
    return house.is_closing();
  }
}