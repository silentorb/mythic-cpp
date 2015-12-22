#pragma once

#include "Glass.h"
#include "lookinglass/Frame.h"

namespace lookinglass {

  class House {
  public:
      Glass* glass;
      Frame*frame;

      House(Frame*frame);
      ~House();
  };
}