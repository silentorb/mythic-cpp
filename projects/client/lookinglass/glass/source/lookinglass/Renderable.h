#pragma once

#include "dllexport.h"

#include "Glass.h"

using namespace std;

namespace lookinglass {
//  class Renderable_List;

  class MYTHIC_EXPORT Renderable {
//      Renderable_List *renderable_list;

  public:
//      Renderable();
      virtual ~Renderable() { }
      virtual void render(Glass &glass) = 0;

      virtual bool is_transparent() { return false; }

//      void set_renderable_list(Renderable_List &value);
  };
}