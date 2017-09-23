#pragma once

#include <bloom/flowers/Flower.h>

namespace bloom {

  struct Modal {
            flowers::Flower *root = nullptr;

            Modal(flowers::Flower *root);
  };

}