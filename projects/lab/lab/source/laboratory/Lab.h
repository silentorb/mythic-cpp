#pragma once

#include "mythic/Mythic_Engine.h"
#include <string>

using namespace mythic;


namespace lookinglass {
  class Renderable;
}
namespace laboratory {

  namespace display {
    class Lab_Renderer;
  }

  class Architecture_Lab;

  class Lab : public Myth {
  private:
      display::Lab_Renderer *renderer;
      void initialize_display();

  public:
      Lab(Mythic_Engine &engine);
      ~Lab();

      std::string get_name() { return "lab"; }

      virtual void update(float delta);

  };
}