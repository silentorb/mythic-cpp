#pragma once

#include <bloom/flowers/Flower.h>

namespace bloom {

  struct Modal {
      Flower *root;
      vector<Flower *> buttons;

      Modal(Flower *root);
  };

}