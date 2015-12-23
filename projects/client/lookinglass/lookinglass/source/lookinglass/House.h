#pragma once

#include "lookinglass/Frame.h"

namespace lookinglass {
  namespace glow {
    class Capabilities;
  }

  class Glass;

  class House {
  private:
      glow::Capabilities *capabilities;

  public:
      Glass *glass;
      Frame &frame;

      House(Frame &frame);
      ~House();
      void start_update();
      void finish_update();
      bool is_closing();
  };
}