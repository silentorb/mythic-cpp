#pragma once

#include "Glass.h"
#include "lookinglass/Frame.h"

namespace lookinglass {

  class House {
  public:
      Glass *glass;
      Frame *frame;

      House(Frame *frame);
      ~House();
      void start_update();
      void finish_update();
      bool is_closing();
  };
}