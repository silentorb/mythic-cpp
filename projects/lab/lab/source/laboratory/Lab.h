#pragma once

#include "mythic/Mythic_Engine.h"
#include <string>
#include <laboratory/display/Freeform_Camera.h>

using namespace mythic;
using namespace laboratory::display;

namespace laboratory {

  namespace display {
    class Lab_Renderer;
  }

  class Lab : public Myth {
  private:
      Freeform_Camera *camera;
      Lab_Renderer *renderer;
      void initialize_display();

  public:
      Lab(Mythic_Engine &engine);
      ~Lab();

      std::string get_name() { return "lab"; }

      virtual void update(float delta);
  };
}