#pragma once

#include "dllexport.h"
#include <memory>

namespace lookinglass {
  class MYTHIC_EXPORT House;

  class MYTHIC_EXPORT Renderable;
}
using namespace lookinglass;

using namespace std;

namespace haft {
  class Input_Manager;
class Input_State;
  class Input_Source;
}

using namespace haft;

namespace clienting {
  class MYTHIC_EXPORT Client {
  private:
      unique_ptr<House> house;
      unique_ptr<Input_Manager> input_manager;
      bool _is_closing;

      Client(const Client &); // no implementation
      Client &operator=(const Client &); // no implementation

  public:
      Client(House *house);

      ~Client();

      void update();
      bool is_closing();
//      void add_renderable(Renderable*renderable);
//      void remove_renderable(Renderable*renderable);

      House &get_house() const {
        return *house;
      }

      Input_Manager &get_input_manager() const {
        return *input_manager.get();
      }

     Input_State &get_current_input_state()const;

      void close() {
        _is_closing = true;
      }
  };
}