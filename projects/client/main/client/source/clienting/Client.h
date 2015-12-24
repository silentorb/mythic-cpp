#pragma once


namespace lookinglass {
  class House;

  class Renderable;
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
//      void add_renderable(Renderable*renderable);
//      void remove_renderable(Renderable*renderable);
      House *get_house();
  };
}