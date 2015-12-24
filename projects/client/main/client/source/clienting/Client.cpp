#include "Client.h"
#include "lookinglass/House.h"

namespace clienting {

  Client::Client(House &house) :
    house(house) {
  }

//  void Client::add_renderable(Renderable *renderable) {
//    house.add_renderable(renderable);
//  }
//
//  void Client::remove_renderable(Renderable *renderable) {
//    house.remove_renderable(renderable);
//  }

  void Client::update() {
    house.update();
  }

  bool Client::is_closing() {
    return house.is_closing();
  }

  House* Client::get_house() {
    return &house;
  }
}