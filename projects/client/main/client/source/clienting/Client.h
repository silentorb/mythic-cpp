#pragma once


namespace lookinglass {
  class House;
}
using namespace lookinglass;

namespace clienting {
  class Client {
  private:
      House &house;

  public:
      Client(House &house);
      void update();
      bool is_closing();
  };
}