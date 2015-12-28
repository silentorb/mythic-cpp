#pragma once

#include <memory>

namespace lookinglass {
  class House;

  class Renderable;
}

using namespace lookinglass;
using namespace std;

namespace clienting {
  class Client {
  private:
      unique_ptr<House> house;

  public:
      Client(House *house);
      void update();
      bool is_closing();
//      void add_renderable(Renderable*renderable);
//      void remove_renderable(Renderable*renderable);

      House &get_house() const {
        return *house;
      }
  };
}