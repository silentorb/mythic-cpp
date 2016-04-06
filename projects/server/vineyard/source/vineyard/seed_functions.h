#pragma once
#include <functional>

namespace vineyard {

  typedef std::function<void(void *)> Seed_Initializer;
  typedef std::function<void *()> Seed_Creator;
}