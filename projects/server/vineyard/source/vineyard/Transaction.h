#pragma once

#include "vineyard/vineyard_export.h"

namespace vineyard {
  class Ground;

  class VINEYARD_EXPORT Transaction {
      Ground &ground;

  public:
      Transaction(Ground &ground);
      ~Transaction();
  };
}