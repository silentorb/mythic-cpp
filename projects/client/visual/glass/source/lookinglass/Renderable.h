#pragma once



#include "Glass.h"
#include<functional>

using namespace std;

namespace lookinglass {
//  class Renderable_List;

  typedef function<void()> Renderable;

//  class Renderable {
////      Renderable_List *renderable_list;
//
//  public:
////      Renderable();
//      virtual ~Renderable() { }
//      virtual void render(Glass &glass) = 0;
//
//      virtual bool is_transparent() { return false; }
//
////      void set_renderable_list(Renderable_List &value);
//  };
}