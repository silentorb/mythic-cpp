#pragma once

#include "commoner/dllexport.h"

#include "mythic/Mythic_Engine.h"
#include <string>

using namespace mythic;

namespace lookinglass {

}
namespace laboratory {
  class Architecture_Lab;

  class Sprite_Lab;

  class Architecture_Lab;

  class MYTHIC_EXPORT Lab : public Myth {
  private:
//      display::Lab_Renderer *renderer;
      void initialize_display();
      unique_ptr<Architecture_Lab> architecture_lab;
      unique_ptr<Sprite_Lab> sprite_lab;
  public:
      Lab(Mythic_Engine &engine);
      ~Lab();

      std::string get_name() { return "lab"; }

      virtual void update(float delta);

  };
}