#pragma once
#include "dllexport.h"

#include "mythic/Mythic_Engine.h"
#include <string>

using namespace mythic;


namespace lookinglass {
  class MYTHIC_EXPORT Renderable;
}
namespace laboratory {
  class MYTHIC_EXPORT Architecture_Lab;

  namespace display {
//    class MYTHIC_EXPORT Lab_Renderer;
  }

  class MYTHIC_EXPORT Architecture_Lab;

  class MYTHIC_EXPORT Lab : public Myth {
  private:
//      display::Lab_Renderer *renderer;
      void initialize_display();
      unique_ptr<Architecture_Lab> architecture_lab;
  public:
      Lab(Mythic_Engine &engine);
      ~Lab();

      std::string get_name() { return "lab"; }

      virtual void update(float delta);

  };
}