#pragma once

#include "commoner/dllexport.h"

#include "Renderable.h"
#include <vector>

using namespace std;

namespace lookinglass {

  class MYTHIC_EXPORT Renderable_List : public Renderable {
  protected:
      vector<Renderable *> renderables;

  public:
      ~Renderable_List();
      void add(Renderable &renderable);
      void remove(Renderable &renderable);

      void render(Glass &glass);
  };
}