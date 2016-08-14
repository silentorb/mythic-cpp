#pragma once

#include "commoner/dllexport.h"

#include "mythic/Mythic_Engine.h"

namespace scenery {
  class Scene;
}

using namespace mythic;

namespace lookinglass {
  class House;
}

namespace typography {
  class Text;
}

namespace laboratory {

  class MYTHIC_EXPORT Sprite_Lab {
  private:
      Mythic_Engine &engine;
      unique_ptr<typography::Text> debug_text;

  public:
      Sprite_Lab(Mythic_Engine &engine);
      ~Sprite_Lab();

      void initialize_lookinglass(lookinglass::House &house);
      void update(float delta);
  };
}