#pragma once

#include <bloom/old/Flower_Old.h>

namespace bloom {

  struct Modal {
      Flower_Old *old_root = nullptr;
      flowers::Flower *root = nullptr;
      vector<Flower_Old *> buttons;

      Modal(Flower_Old *root);
      Modal(flowers::Flower *root);
  };

}