#pragma once

#include "dllexport.h"

namespace vineyard {
  class Ground;

  class MYTHIC_EXPORT Transaction {
      Ground &ground;

  public:
      Transaction(Ground &ground);
      ~Transaction();
  };
}