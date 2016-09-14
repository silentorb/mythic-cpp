#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include <functional>
#include <vector>

namespace timing {
  class Quartz;
}

namespace clienting {
  class Client;
}
namespace platforming {
  class Platform_Factory;
}
namespace lookinglass {
  class Graphic_Options;
}
using namespace std;

namespace mythic {

  class Mythic_Renderer;

  typedef std::function<void(float)> Update_Delegate;

  class MYTHIC_EXPORT Mythic_Engine : no_copy {
      unique_ptr<timing::Quartz> timer;
      unique_ptr<clienting::Client> client;
      Update_Delegate update_delegate;

  public:
      Mythic_Engine(platforming::Platform_Factory &factory, const lookinglass::Graphic_Options &graphic_options);
      ~Mythic_Engine();

      void add_external_myth(const Update_Delegate &update_delegate) {
        this->update_delegate = update_delegate;
      }

      void update();
      void loop();

      clienting::Client &get_client() const {
        return *client;
      }

  };
}