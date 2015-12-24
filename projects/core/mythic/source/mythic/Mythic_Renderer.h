#pragma once

#include "lookinglass/Renderable.h"
#include <vector>

using namespace lookinglass;

namespace mythic {

  class Mythic_Renderer : public Renderable {
  private:
      std::vector<Renderable *> renderables;
  public:
      void render(Glass &glass);
      void add_renderable(Renderable *renderable);
      void remove_renderable(Renderable *renderable);
  };
}