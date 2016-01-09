#include "Client.h"
#include "lookinglass/House.h"
#include "haft/Input_Manager.h"

namespace clienting {

  Client::Client(House *house, Input_Source*input_source) :
    house(house),
    input_manager(new Input_Manager(input_source))
  {
  }

  Client::~Client() { }


  void Client::update() {
    house->update();
  }

  bool Client::is_closing() {
    return house->is_closing();
  }

}