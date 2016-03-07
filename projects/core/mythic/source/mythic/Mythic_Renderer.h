#pragma once
#include "dllexport.h"

#include "lookinglass/Renderable.h"
#include <vector>

using namespace lookinglass;

namespace mythic {

  class MYTHIC_EXPORT Mythic_Renderer {
  private:
      std::vector<Renderable> renderables;
  public:
      void render();
      void add_renderable(Renderable renderable);
//      void remove_renderable(Renderable *renderable);
  };
}