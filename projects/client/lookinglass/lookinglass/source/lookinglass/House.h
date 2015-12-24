#pragma once

#include "lookinglass/Frame.h"
#include <vector>

using namespace std;

namespace lookinglass {
  namespace glow {
    class Capabilities;
  }

  class Glass;
  class Renderable;

  class House {
  private:
      glow::Capabilities *capabilities;
      vector<Renderable *> renderables;

  public:
      Glass *glass;
      Frame &frame;

      House(Frame &frame);
      ~House();
      void update();
      bool is_closing();
      void add_renderable(Renderable *renderable);
      void remove_renderable(Renderable*renderable);
  };
}