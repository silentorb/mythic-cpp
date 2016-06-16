#pragma once

#include <bloom/flowers/Flower_Old.h>

namespace bloom {

  struct Modal {
      Flower_Old *root;
      vector<Flower_Old *> buttons;

      Modal(Flower_Old *root);
  };

}